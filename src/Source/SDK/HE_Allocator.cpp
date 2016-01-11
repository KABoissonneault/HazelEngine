#include "HE_Allocator.h"

#include "HE_Assert.h"
#include "HE_Platform.h"

namespace HE
{
	Blk MallocAllocator::allocate(size_t n)
	{
		return{ MALLOC(n), n };
	}

	Blk MallocAllocator::allocate(size_t n, size_t aligned)
	{
		return{ ALIGNED_MALLOC(n, aligned), n };
	}

	void MallocAllocator::deallocate(Blk blk)
	{
		return FREE(blk.ptr);
	}

	Blk NullAllocator::allocate(size_t)
	{
		return{ nullptr, 0 };
	}

	Blk NullAllocator::allocate(size_t, size_t)
	{
		return{ nullptr, 0 };
	}

	void NullAllocator::deallocate(Blk b) noexcept
	{
		ASSERT(b.ptr == nullptr);
	}
	void NullAllocator::deallocateAll() noexcept
	{

	}
	bool NullAllocator::owns(Blk b)
	{
		return b.ptr == nullptr;
	}
}