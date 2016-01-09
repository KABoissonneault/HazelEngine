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
}