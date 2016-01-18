#include <gtest/gtest.h>

#include "HE_Allocator.h"
#include "HE_Platform.h"

using namespace HE;


namespace
{
	template<class T>
	constexpr bool IsAligned(const T* const p, size_t const alignment) noexcept
	{
		return reinterpret_cast<size_t>(p) % alignment == 0;
	}
}

TEST(NullAllocator, Allocate)
{
	EXPECT_EQ(nullptr, allocate<size_t>(NullAllocator::it).ptr);
}

TEST(NullAllocator, Owns)
{
	EXPECT_TRUE(NullAllocator::it.owns({ nullptr, 0 }));
	EXPECT_FALSE(NullAllocator::it.owns({ reinterpret_cast<void*>(0xABCDEF), 8 }));
}

TEST(StackAllocator, Allocate)
{
	StackAllocator<64> a;
	auto const blk1 = a.allocate(16);
	EXPECT_EQ(16, blk1.length);
	EXPECT_NE(nullptr, blk1.ptr);
	EXPECT_NO_FATAL_FAILURE(*reinterpret_cast<size_t*>(blk1.ptr) = 16ull);
}

TEST(StackAllocator, AllocateSmall)
{
	StackAllocator<64> a;
	auto const blk1 = a.allocate(1);
	EXPECT_EQ(1, blk1.length);
	EXPECT_NE(nullptr, blk1.ptr);
	EXPECT_NO_FATAL_FAILURE(*reinterpret_cast<char*>(blk1.ptr) = 16);
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

TEST(StackAllocator, AlignedAlloc)
{
	StackAllocator<64> a;
	auto const b = a.allocate(sizeof(char));

	auto const b2 = a.allocate(sizeof(size_t), alignof(size_t));
	EXPECT_TRUE(IsAligned(b2.ptr, alignof(size_t)));
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

TEST(StackAllocator, DeallocateAll)
{
	StackAllocator<8*sizeof(size_t)> a;
	auto const b1 = allocate<size_t>(a, 8);
	a.deallocateAll();

	auto const b2 = allocate<size_t>(a);
	EXPECT_NE(nullptr, b2.ptr);
}

TEST(MallocAllocator, AllocateTest)
{
	auto const blk1 = MallocAllocator::it.allocate(sizeof(size_t));
	EXPECT_EQ(sizeof(size_t), blk1.length);
	EXPECT_TRUE(blk1.ptr != nullptr || errno == ENOMEM);
	EXPECT_NE(EINVAL, errno);
	EXPECT_NO_FATAL_FAILURE(*reinterpret_cast<size_t*>(blk1.ptr) = 42ull);
}

TEST(MallocAllocator, DeallocateTest)
{
	auto const blk = MallocAllocator::it.allocate(sizeof(size_t));
	EXPECT_NO_FATAL_FAILURE(MallocAllocator::it.deallocate(blk));
	EXPECT_NO_FATAL_FAILURE(MallocAllocator::it.deallocate({ nullptr, 0 }));
}

TEST(AlignedMallocAllocator, AllocateTest)
{
	auto const blk1 = AlignedMallocAllocator::it.allocate(sizeof(size_t));
	EXPECT_EQ(sizeof(size_t), blk1.length);
	EXPECT_TRUE(blk1.ptr != nullptr || errno == ENOMEM);
	EXPECT_NE(EINVAL, errno);
	EXPECT_NO_FATAL_FAILURE(*reinterpret_cast<size_t*>(blk1.ptr) = 42ull);
}

TEST(AlignedMallocAllocator, AlignedAllocate)
{
	auto const b1 = AlignedMallocAllocator::it.allocate(256, 16);
	EXPECT_TRUE(b1.ptr != nullptr || errno == ENOMEM);
	EXPECT_NE(EINVAL, errno);
	EXPECT_TRUE(IsAligned(b1.ptr, 16));
}

TEST(AlignedMallocAllocator, Deallocate)
{
	auto const blk = AlignedMallocAllocator::it.allocate(sizeof(size_t));
	EXPECT_NO_FATAL_FAILURE(AlignedMallocAllocator::it.deallocate(blk));
	EXPECT_NO_FATAL_FAILURE(AlignedMallocAllocator::it.deallocate({ nullptr, 0 }));
}

TEST(FallbackAllocator, Allocate)
{
	FallbackAllocator<NullAllocator, MallocAllocator> a;
	auto const b = a.allocate(sizeof(size_t));
	EXPECT_NE(nullptr, b.ptr);
	EXPECT_EQ(sizeof(size_t), b.length);
	EXPECT_NO_FATAL_FAILURE(*reinterpret_cast<size_t*>(b.ptr) = 42ull);
}

TEST(FallbackAllocator, FallbackAllocate)
{
	FallbackAllocator<NullAllocator, MallocAllocator> a;
	auto const b = a.allocate(sizeof(size_t) * 32);
	EXPECT_TRUE(b.ptr != nullptr || errno == ENOMEM); // Malloc might return null if out of memory, but that's a very rare case if you're just running tests...
	EXPECT_NO_FATAL_FAILURE(reinterpret_cast<size_t*>(b.ptr)[31] = 42ull);
}

TEST(FallbackAllocator, Owns)
{
	// FallbackAllocator is only a OwningAllocator if the fallback allocator is an OwningAllocator (the primary one must be Owning anyway)
	FallbackAllocator<NullAllocator, LightInlineAllocator<16>> a;
	auto const b = a.allocate(sizeof(size_t));
	EXPECT_TRUE(a.owns(b));
}

TEST(FallbackAllocator, Deallocate)
{
	FallbackAllocator<NullAllocator, MallocAllocator> a;
	auto const blk = a.allocate(sizeof(size_t));
	EXPECT_NO_FATAL_FAILURE(a.deallocate(blk));
	EXPECT_NO_FATAL_FAILURE(a.deallocate({ nullptr, 0 }));
}

TEST(FreelistAllocator, Allocate)
{
	FreelistAllocator<MallocAllocator, 16> a;
	auto const b = allocate<char>(a);
	EXPECT_NE(nullptr, b.ptr);
	EXPECT_EQ(sizeof(char), b.length);
	EXPECT_NO_FATAL_FAILURE(*reinterpret_cast<size_t*>(b.ptr) = 42ull);
}

TEST(FreelistAllocator, FreelistAllocate)
{
	FreelistAllocator<MallocAllocator, 16> a;
	auto const b = a.allocate(16);
	EXPECT_NE(nullptr, b.ptr);
	EXPECT_EQ(16, b.length);
	EXPECT_NO_FATAL_FAILURE(reinterpret_cast<size_t*>(b.ptr)[0] = 42ull);
}

TEST(FreelistAllocator, MidrangeFreelistAllocate)
{
	FreelistAllocator<MallocAllocator, 17, 32> a;
	auto const b = a.allocate(23);
	EXPECT_NE(nullptr, b.ptr);
	EXPECT_EQ(32, b.length);
	EXPECT_NO_FATAL_FAILURE(reinterpret_cast<size_t*>(b.ptr)[0] = 42ull);
}

TEST(FreelistAllocator, Owns)
{
	// FreelistAllocator is only a OwningAllocator if the parent allocator is an OwningAllocator
	FreelistAllocator<NullAllocator, 16> a;
	auto const b = a.allocate(sizeof(size_t));
	EXPECT_TRUE(a.owns(b));
}

TEST(FreelistAllocator, Deallocate)
{
	FreelistAllocator<MallocAllocator, 16> a;
	auto const blk = a.allocate(sizeof(size_t));
	EXPECT_NO_FATAL_FAILURE(a.deallocate(blk));
	EXPECT_NO_FATAL_FAILURE(a.deallocate({ nullptr, 0 }));

	auto const blk1 = a.allocate(16);
	EXPECT_NO_FATAL_FAILURE(a.deallocate(blk1));
}

TEST(AffixAllocator, StatelessAllocate)
{
	using Affix = AffixAllocator<MallocAllocator, size_t>;
	auto const b = allocate<size_t>(Affix::it);
	EXPECT_NE(nullptr, b.ptr);
	EXPECT_EQ(sizeof(size_t), b.length);
	EXPECT_NO_FATAL_FAILURE(*reinterpret_cast<size_t*>(b.ptr) = size_t{ 42 });
}

TEST(AffixAllocator, StatefulAllocate)
{
	using Affix = AffixAllocator<MallocAllocator, size_t>;
	Affix a;
	auto const b = allocate<size_t>(a);
	EXPECT_NE(nullptr, b.ptr);
	EXPECT_EQ(sizeof(size_t), b.length);
	EXPECT_NO_FATAL_FAILURE(*reinterpret_cast<size_t*>(b.ptr) = size_t{ 42 });
}

TEST(AffixAllocator, Owns)
{
	using Affix = AffixAllocator<NullAllocator, size_t>;
	Affix a;
	auto const b = allocate<size_t>(a);
	EXPECT_TRUE(a.owns(b));
}

TEST(AffixAllocator, Deallocate)
{
	using Affix = AffixAllocator<MallocAllocator, size_t>;
	auto const blk = Affix::it.allocate(sizeof(size_t));
	EXPECT_NO_FATAL_FAILURE(Affix::it.deallocate(blk));
	EXPECT_NO_FATAL_FAILURE(Affix::it.deallocate({ nullptr, 0 }));
}

TEST(AffixAllocator, Affix)
{
	using Affix = AffixAllocator<MallocAllocator, size_t, size_t>;

	auto b = Affix::it.allocate(16);
	auto const p = static_cast<unsigned long long*>(b.ptr);
	p[0] = 0;
	p[1] = 0;
	EXPECT_NO_FATAL_FAILURE(Affix::Prefix(b) = 0xFFFFFFFFFFFFFFFULL);
	EXPECT_NO_FATAL_FAILURE(Affix::Suffix(b) = 0xFFFFFFFFFFFFFFFULL);
	EXPECT_TRUE(p[0] == 0 && p[0] == 0); // Expect the data to be intact
}