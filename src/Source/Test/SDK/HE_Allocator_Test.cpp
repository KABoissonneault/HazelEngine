#include <gtest/gtest.h>

#include "HE_Allocator.h"

using namespace HE;

TEST(StackAllocator, AllocateTest)
{
	StackAllocator<64> a;
	auto const blk1 = a.allocate(16);
	EXPECT_EQ(16, blk1.length);
	EXPECT_NE(nullptr, blk1.ptr);
	EXPECT_NO_FATAL_FAILURE(*reinterpret_cast<size_t*>(blk1.ptr) = 16ull);
}

TEST(StackAllocator, AllocateFail)
{
	StackAllocator<64> a;
	auto const blk1 = a.allocate(128);
	EXPECT_EQ(nullptr, blk1.ptr);

	auto const blk2 = a.allocate(32);
	auto const blk3 = a.allocate(48);
	EXPECT_EQ(nullptr, blk3.ptr);
}

TEST(StackAllocator, Owns)
{
	StackAllocator<64> a;
	auto const b = a.allocate(sizeof(size_t));
	EXPECT_TRUE(a.owns(b));
}

TEST(StackAllocator, DeallocateTest)
{
	StackAllocator<64> a;
	auto const blk1 = a.allocate(32);
	
	EXPECT_NO_FATAL_FAILURE(a.deallocate(blk1));
	EXPECT_NO_FATAL_FAILURE(a.deallocate({ nullptr, 0 }));

	// We expect to be able to allocate 64 bytes again
	EXPECT_NE(nullptr, a.allocate(64).ptr);
}

TEST(MallocAllocator, AllocateTest)
{
	MallocAllocator a;
	auto const blk1 = a.allocate(sizeof(size_t));
	EXPECT_EQ(sizeof(size_t), blk1.length);
	EXPECT_NO_FATAL_FAILURE(*reinterpret_cast<size_t*>(blk1.ptr) = 42ull);
}

TEST(MallocAllocator, DeallocateTest)
{
	MallocAllocator a;
	auto const blk = a.allocate(sizeof(size_t));
	EXPECT_NO_FATAL_FAILURE(a.deallocate(blk));
	EXPECT_NO_FATAL_FAILURE(a.deallocate({ nullptr, 0 }));
}

TEST(FallbackAllocator, AllocateTest)
{
	FallbackAllocator<StackAllocator<64>, MallocAllocator> a;
	auto const b = a.allocate(sizeof(size_t));
	EXPECT_EQ(sizeof(size_t), b.length);
	EXPECT_NO_FATAL_FAILURE(*reinterpret_cast<size_t*>(b.ptr) = 42ull);
}

TEST(FallbackAllocator, FallbackAllocateTest)
{
	FallbackAllocator<StackAllocator<64>, MallocAllocator> a;
	auto const b = a.allocate(sizeof(size_t) * 32);
	EXPECT_NE(nullptr, b.ptr); // Malloc might return null if out of memory, but that's a very rare case if you're just running tests...
	EXPECT_NO_FATAL_FAILURE(reinterpret_cast<size_t*>(b.ptr)[31] = 42ull);
}

TEST(FallbackAllocator, Owns)
{
	// FallbackAllocator is only a OwningAllocator if the fallback allocator is an OwningAllocator (the primary one must be Owning anyway)
	FallbackAllocator<StackAllocator<64>, StackAllocator<512>> a;
	auto const b = a.allocate(sizeof(size_t));
	EXPECT_TRUE(a.owns(b));
}

TEST(FallbackAllocator, DeallocateTest)
{
	FallbackAllocator<StackAllocator<64>, MallocAllocator> a;
	auto const blk = a.allocate(sizeof(size_t));
	EXPECT_NO_FATAL_FAILURE(a.deallocate(blk));
	EXPECT_NO_FATAL_FAILURE(a.deallocate({ nullptr, 0 }));
}