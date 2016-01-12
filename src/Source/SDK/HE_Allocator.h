#pragma once

#include <gsl.h>

#include "TMP_Helper.h"
#include "HE_String.h"
#include "HE_Assert.h"
#include "HE_Math.h"

#include <type_traits>

namespace HE
{
	struct MemoryBlock
	{
		void* ptr;
		size_t length;
	};
	using Blk = MemoryBlock;

	// Max alignment
	constexpr size_t PlatformMaxAlignment = Math::Max(alignof(void*), alignof(long double), alignof(size_t));
	static_assert(Math::IsPow2(PlatformMaxAlignment), "PlatformMaxAlignment is not a power of 2, as should be");

	namespace Private
	{
		template<class T>
		using try_allocate = std::enable_if_t<std::is_same<Blk, decltype(std::declval<T>().allocate(std::declval<size_t>()))>::value>;

		// Custom aligned allocation's alignment parameter generally has to be a power of 2 and bigger than the allocator's default alignment,
		// in order to respect the allocator's semantics
		template<class T>
		using try_aligned_allocate = std::enable_if_t<std::is_same<Blk, decltype(std::declval<T>().allocate(std::declval<size_t>(), std::declval<size_t>()))>::value>;

		template<class T>
		using try_deallocate = std::enable_if_t<noexcept(std::declval<T>().deallocate(std::declval<Blk>()))>;

		template<class T>
		using try_deallocateAll = std::enable_if_t<noexcept(std::declval<T>().deallocateAll())>;

		template<class T>
		using try_owns = std::enable_if_t<std::is_same<bool, decltype(std::declval<T>().owns(std::declval<Blk>()))>::value>;
	}

	// Allocator
	// Must have (for allocator of type T): 
	// - MemoryBlock T::allocate(size_t)
	// - void T::deallocate(MemoryBlock)
	template<class T>
	using is_allocator = and_ < has_op<T, Private::try_allocate>, has_op<T, Private::try_deallocate> > ;
	template<class... T>
	constexpr bool IsAllocator()
	{
		return and_<is_allocator<T>...>::value;
	}

	// OwningAllocator
	// Must have (for allocator of type T)
	// - HE::is_allocator<T>()
	// - bool T::owns(MemoryBlock)
	template<class T>
	using is_owning_allocator = and_<is_allocator<T>, has_op<T, Private::try_owns>>;
	template<class... T>
	constexpr bool IsOwningAllocator()
	{
		return and_<is_owning_allocator<T>...>::value;
	}

	// AlignedAllocator
	// Must have (for allocator of type T)
	// - HE::is_allocator<T>()
	// - bool T::allocate(size_t, size_t)
	template<class T>
	using is_aligned_allocator = and_<is_allocator<T>, has_op<T, Private::try_aligned_allocate>>;
	template<class... T>
	constexpr bool IsAlignedAllocator()
	{
		return and_<is_aligned_allocator<T>...>::value;
	}

	// Generic allocator functions
	template< class Type, class Allocator, class Enable = std::enable_if_t<is_allocator<Allocator>::value>>
	Blk allocate(Allocator&& a)
	{
		return a.allocate(sizeof(Type));
	}

	template<class Type, class Allocator, class Enable = std::enable_if_t<is_allocator<Allocator>::value>>
	Blk allocate(Allocator&& a, size_t count)
	{
		return a.allocate(count*sizeof(Type), alignof(Type));
	}

	class NullAllocator
	{
	public:
		static constexpr size_t alignment = 64 * 1024;

		Blk allocate(size_t);
		Blk allocate(size_t, size_t);
		void deallocate(Blk) noexcept;
		void deallocateAll() noexcept;
		bool owns(Blk);
	};

	template<size_t S>
	class StackAllocator 
	{
	public:
		static constexpr size_t size = S;
		static constexpr size_t alignment = PlatformMaxAlignment;

		Blk allocate(size_t const n)
		{
			return allocate(n, alignment);
		}

		// Aligned allocation
		Blk allocate(size_t const n, size_t const custom_alignement)
		{
			EXPECTS(Math::IsPow2(alignment) && custom_alignement >= alignment);

			auto const a = offsetToAligned(n, custom_alignement);
			auto const n1 = n + a; // Total allocated memory

			if (n1 > leftoverMemory())
				return{ nullptr, 0 };

			// Return the aligned pointer and the requested size
			// Note that even though more memory might have been "allocated"
			// due to alignment requirements, that memory is not part of the
			// current allocation, but will be restored once the previous one is deallocated
			Blk const result{ m_pSentinel + a, n };
			m_pSentinel += n1;
			return result;
		}

		void deallocate(Blk const blk) noexcept
		{
			if (blk.ptr != nullptr)
			{
				ASSERT_MSG(blk.ptr == m_pSentinel - blk.length, Format("MemoryBlock(ptr={_}, length={_}) was deallocated out of order", blk.ptr, blk.length));
				m_pSentinel = static_cast<char*>(blk.ptr);
			}
		}

		void deallocateAll() noexcept
		{
			m_pSentinel = m_Buffer;
		}

		bool owns(Blk const blk)
		{
			return blk.ptr >= m_Buffer && blk.ptr < (m_Buffer + blk.length);
		}

	private:
		size_t offsetToAligned(size_t const n, size_t const alignment) const noexcept
		{
			auto const offsetFromAlignment = reinterpret_cast<size_t>(m_pSentinel) & (alignment - 1); // The distance past the previous aligned value
			
			if (offsetFromAlignment == 0)
			{
				return 0;
			}
			// If the allocated memory is smaller than the space we have from
			// the current sentry position to the alignment requirement,
			// assume we only have to align to the memory size
			// ex: m_pSentry == &m_Buffer[1] -> allocate(2) -> offsetToAligned(2, 8) -> offsetToAligned(2, 2) (since 2 < 8 - 1) -> 1
			else if (n < alignment - offsetFromAlignment && Math::IsPow2(n))
			{
				return offsetToAligned(n, n);
			}
			else
			{
				return (alignment - offsetFromAlignment);
			}
		}

		size_t leftoverMemory() const noexcept
		{
			return S - static_cast<size_t>(m_pSentinel - m_Buffer);
		}

		char m_Buffer[S];
		char* m_pSentinel{ m_Buffer };
	};	

	class MallocAllocator
	{
	public:
		static constexpr size_t alignment = PlatformMaxAlignment;

		Blk allocate(size_t n);
		void deallocate(Blk) noexcept;
	};

	class AlignedMallocAllocator
	{
	public:
		static constexpr size_t alignment = PlatformMaxAlignment;

		Blk allocate(size_t n);
		Blk allocate(size_t n, size_t alignment);
		void deallocate(Blk) noexcept;
	};

	template< class Primary, class Fallback >
	class FallbackAllocator :
		private Primary,
		private Fallback
	{
	protected:
		using P = Primary;
		using F = Fallback;

		static_assert(IsOwningAllocator<P>(), "Primary allocator does not meet the HE::OwningAllocator concept");
		static_assert(IsAllocator<F>(), "Fallback allocator does not meet the HE::Allocator concept");

	public:
		static constexpr size_t alignment = Math::Min(Primary::alignment, Fallback::alignment);

		Blk allocate(size_t n)
		{
			auto const blk = P::allocate(n);
			if (!blk.ptr) return F::allocate(n);
			return blk;
		}

		template<class Enable = std::enable_if_t<and_<is_aligned_allocator<Primary>, is_aligned_allocator<Fallback>>::value>>
		Blk allocate(size_t n, size_t alignment)
		{
			auto const blk = P::allocate(n, alignment);
			if (!blk.ptr) return F::allocate(n, alignment);
			return blk;
		}

		void deallocate(Blk b) noexcept
		{
			if (P::owns(b))
				P::deallocate(b);
			else
				F::deallocate(b);
		}

		template<class Enable = std::enable_if_t<and_<has_op<Primary, Private::try_deallocateAll>, has_op<Fallback, Private::try_deallocateAll>>::value>>
		void deallocateAll() noexcept
		{
			Primary::deallocateAll();
			Fallback::deallocateAll();
		}
		

		template<class Enable = std::enable_if_t<is_owning_allocator<Fallback>::value>>
		bool owns(Blk b)
		{
			return Primary::owns(b) || Fallback::owns(b);
		}
	};

	namespace Allocator
	{
		constexpr size_t unbounded = static_cast<size_t>(-1);
	}

	// An allocator that allocates nodes on a Parent allocator and internally keeps blocks
	// of memory on deallocation instead of actually deallocating them, but only
	// if they have a certain size

	// minSize: Minimum size of the allocation to be considered in range
	// maxSize: Maxsimum size of the allocation to be considered in range
	// batchCount: Number of allocations on a fresh "in range" allocation. Basically fills up the Freelist with batchCount nodes on allocation
	// maxNodes: Max number of nodes the freelist can keep
	template< class Parent,
		size_t MinSize, 
		size_t MaxSize = MinSize,
		size_t BatchCount = 8,
		size_t MaxNodes = Allocator::unbounded,
		class Enable = std::enable_if_t<is_allocator<Parent>::value>
		>
	class FreelistAllocator
		: private Parent
	{
		static_assert(BatchCount <= MaxNodes, "batchCount should be smaller or equal to maxNodes");

	public:
		static constexpr size_t alignment = Parent::alignment;

		Blk allocate(size_t n)
		{
			return allocateImpl(n);
		}

		template<class Enable = std::enable_if_t<is_aligned_allocator<Parent>::value>>
		Blk allocate(size_t n, size_t alignment)
		{
			return allocateImpl(n, alignment);
		}

		void deallocate(Blk b)
		{
			if (m_nNodesCount != MaxNodes && inRange(b.length))
			{
				auto const next = m_pFreelistRoot;
				m_pFreelistRoot = static_cast<Node*>(b.ptr);
				m_pFreelistRoot.next = next;
				++m_nNodesCount;
			}
			else
			{
				Parent::deallocate(b);
			}
		}

		template<class Enable = std::enable_if_t<has_op<Parent, Private::try_deallocateAll>::value>>
		void deallocateAll()
		{
			Parent::deallocateAll();
			_root = nullptr;
		}

		template<class Enable = std::enable_if_t<is_owning_allocator<Parent>::value>>
		bool owns(Blk b)
		{
			return Parent::owns(b);
		}

	private:
		struct Node
		{
			Node* next;
		};
		Node* m_pFreelistRoot{ nullptr };
		size_t m_nNodesCount{ 0 };

		bool inRange(size_t n) const
		{
			if (MinSize == MaxSize) return n == MaxSize;

			return (MinSize == 0 || n >= MinSize) && n <= MaxSize;
		}

		template<class... Args>
		Blk allocateImpl(size_t n, Args... args)
		{
			if (!inRange(n)) return Parent::allocate(n, args...);

			n = MaxSize;
			if (!m_pFreelistRoot) return allocateNewBlocks(n, args...);

			Blk const result{ static_cast<void*>(m_pFreelistRoot), n };
			m_pFreelistRoot = m_pFreelistRoot->next;
			--m_nNodesCount;
			return result;
		}

		template<class... Args>
		Blk allocateNewBlocks(size_t n, Args... args)
		{
			if (MaxNodes == 1) return Parent::allocate(n, args...);

			auto batch = Parent::allocate(BatchCount * n);
			if (!batch.ptr) return batch;

			Blk const result{ batch.ptr, n };
			Blk rest{ static_cast<char*>(batch.ptr) + n, batch.length - n };
			m_pFreelistRoot = static_cast<Node*>(rest.ptr);

			while (rest.length >= n)
			{
				batch = rest;
				rest = { static_cast<char*>(batch.ptr) + n, batch.length - n};
				static_cast<Node*>(batch.ptr)->next = static_cast<Node*>(rest.ptr);
			}

			m_nNodesCount = BatchCount - 1;
			
			return result;
		}
	};
}