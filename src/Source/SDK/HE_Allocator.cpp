#include "HE_Allocator.h"

#include "HE_Assert.h"

namespace HE
{
	Blk MallocAllocator::allocate(size_t n)
	{
		return{ std::malloc(n), n };
	}

	void MallocAllocator::deallocate(Blk blk)
	{
		return std::free(blk.ptr);
	}
}