#include "HE_Allocator.h"

#include "HE_Assert.h"
#include "HE_Platform.h"

namespace HE
{
	NullAllocator NullAllocator::it;
	MallocAllocator MallocAllocator::it;
	AlignedMallocAllocator AlignedMallocAllocator::it;


	Blk MallocAllocator::allocate(size_t n)
	{
		return{ std::malloc(n), n };
	}

	void MallocAllocator::deallocate(Blk blk) noexcept
	{
		std::free(blk.ptr);
	}

	Blk AlignedMallocAllocator::allocate(size_t n)
	{
		return{ ALIGNED_MALLOC(n, alignment), n };
	}

	Blk AlignedMallocAllocator::allocate(size_t n, size_t a)
	{
		EXPECTS(Math::IsPow2(a) && a >= alignment);
		return{ ALIGNED_MALLOC(n, a), n };
	}

	void AlignedMallocAllocator::deallocate(Blk b) noexcept
	{
		ALIGNED_FREE(b.ptr);
	}

	Blk NullAllocator::allocate(size_t n)
	{
		return{ nullptr, n };
	}

	Blk NullAllocator::allocate(size_t n, size_t)
	{
		return{ nullptr, n };
	}

	void NullAllocator::deallocate(Blk b) noexcept
	{
		EXPECTS(b.ptr == nullptr);
	}

	void NullAllocator::deallocateAll() noexcept
	{

	}

	bool NullAllocator::owns(Blk b)
	{
		return b.ptr == nullptr;
	}
}