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


	namespace Private
	{
		template<class T>
		using try_allocate = std::enable_if_t<std::is_same<Blk, decltype(std::declval<T>().allocate(std::declval<size_t>()))>::value>;

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

	template< class Type, class Allocator, class Enable = std::enable_if_t<is_aligned_allocator<Allocator>::value>>
	Blk allocate_aligned(Allocator&& a)
	{
		return a.allocate(sizeof(Type), alignof(Type));
	}

	template<class Type, class Allocator, class Enable = std::enable_if_t<is_aligned_allocator<Allocator>::value>>
	Blk allocate_aligned(Allocator&& a, size_t count)
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

		Blk allocate(size_t const n, size_t const alignment)
		{
			EXPECTS(Math::IsPow2(alignment));
			auto const a = offsetToAligned(n, alignment);
			auto const n1 = n + a; // Total allocated memory

			if (n1 > S - static_cast<size_t>(m_pSentinel - m_Buffer))
				return{ nullptr, 0 };
			
			Blk const result{ m_pSentinel + a, n }; // Return the aligned pointer
			m_pSentinel += n1;
			return result;
		}

		void deallocate(Blk const blk) noexcept
		{
			if (blk.ptr != nullptr)
			{
				ASSERT_MSG(blk.ptr >= m_pSentinel - blk.length, Format("MemoryBlock(ptr={_}, length={_}) was deallocated out of order", blk.ptr, blk.length));
				m_pSentinel -= blk.length;
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
		size_t offsetToAligned(size_t const n, size_t const alignment)
		{
			EXPECTS(Math::IsPow2(alignment));
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

		char m_Buffer[S];
		char* m_pSentinel{ m_Buffer };
	};	

	class MallocAllocator
	{
	public:
		static constexpr size_t alignment = PlatformMaxAlignment;

		Blk allocate(size_t);
		Blk allocate(size_t, size_t alignment);
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
}