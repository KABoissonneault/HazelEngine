#pragma once

#include "TMP_Helper.h"
#include "HE_String.h"

#include <type_traits>

namespace HE
{
	struct MemoryBlock
	{
		void* ptr;
		size_t length;
	};
	using Blk = MemoryBlock;

	namespace AllocatorPrivate
	{
		template<class T>
		using try_allocate = std::enable_if_t<std::is_same<Blk, decltype(std::declval<T>().allocate(std::declval<size_t>()))>::value>;

		template<class T>
		using try_deallocate = decltype(std::declval<T>().deallocate(std::declval<Blk>()));

		template<class T>
		using try_owns = std::enable_if_t<std::is_same<bool, decltype(std::declval<T>().owns(std::declval<Blk>()))>::value>;
	}

	// Template alias for the Allocator concept
	// Must have (Allocator of type T): 
	// - MemoryBlock T::allocate(size_t)
	// - void T::deallocate(MemoryBlock)
	template<class T>
	using is_allocator = and_<has_op<T, AllocatorPrivate::try_allocate>, has_op<T, AllocatorPrivate::try_deallocate>>;
	template<class... T>
	constexpr bool IsAllocator()
	{
		return and_<is_allocator<T>...>::value;
	}

	// Template alias for the OwningAllocator concept
	// Must have (Allocator of type T)
	// - HE::is_allocator<T>()
	// - bool T::owns(MemoryBlock)
	template<class T>
	using is_owning_allocator = and_<is_allocator<T>, has_op<T, AllocatorPrivate::try_owns>>;
	template<class... T>
	constexpr bool IsOwningAllocator()
	{
		return and_<is_owning_allocator<T>...>::value;
	}

	template<size_t S>
	class StackAllocator 
	{
	public:
		Blk allocate(size_t n)
		{
			if (m_pSentinel + n - &m_Buffer[0] > S)
				return{ nullptr, 0 };

			auto const p = m_pSentinel;
			m_pSentinel += n;
			return{ p, n };
		}

		void deallocate(Blk blk)
		{
			if (blk.ptr != nullptr)
			{
				ASSERT_MSG(blk.ptr == m_pSentinel - blk.length, Format("MemoryBlock(ptr={_}, length={_}) was deallocated out of order", blk.ptr, blk.length));
				m_pSentinel -= blk.length;
			}
		}

		bool owns(Blk blk)
		{
			return blk.ptr >= &m_Buffer[0] && blk.ptr <= (m_pSentinel - blk.length);
		}

	private:
		char m_Buffer[S];
		char* m_pSentinel{ &m_Buffer[0] };
	};	

	class MallocAllocator
	{
	public:
		Blk allocate(size_t);
		void deallocate(Blk);
	};

	namespace AllocatorPrivate
	{
		template< class Primary, class Fallback >
		class FallbackAllocatorImpl :
			protected Primary,
			protected Fallback
		{
		protected:
			using P = Primary;
			using F = Fallback;

			static_assert(IsOwningAllocator<P>(), "Primary allocator does not meet the HE::OwningAllocator concept");
			static_assert(IsAllocator<F>(), "Fallback allocator does not meet the HE::Allocator concept");

		public:
			Blk allocate(size_t n)
			{
				auto const blk = P::allocate(n);
				if (!blk.ptr) return F::allocate(n);
				return blk;
			}

			void deallocate(Blk b)
			{
				if (P::owns(b))
					P::deallocate(b);
				else
					F::deallocate(b);
			}
		};
	}

	template< class Primary, class Fallback, class Enable = void >
	class FallbackAllocator :
		public AllocatorPrivate::FallbackAllocatorImpl<Primary, Fallback>
	{
	};

	template< class Primary, class Fallback>
	class FallbackAllocator<Primary, Fallback, std::enable_if_t<is_allocator<Fallback>::value>> :
		public AllocatorPrivate::FallbackAllocatorImpl<Primary, Fallback>
	{
	public:
		bool owns(Blk b)
		{
			return P::owns(b) || F::owns(b);
		}
	};

	
	
}