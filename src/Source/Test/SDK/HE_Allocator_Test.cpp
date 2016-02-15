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

TEST(LightInlineAllocator, Allocate)
{
	LightInlineAllocator<16> a;
	auto const b = allocate<size_t>(a);
	EXPECT_NE(nullptr, b.ptr);
	EXPECT_EQ(sizeof(size_t), b.length);
	EXPECT_NO_FATAL_FAILURE(*reinterpret_cast<size_t*>(b.ptr) = 42ull);
}

TEST(LightInlineAllocator, AllocateAligned)
{
	LightInlineAllocator<64> a;
	auto const b = a.allocate(sizeof(size_t) * 4, alignof(size_t) * 4);
	EXPECT_NE(nullptr, b.ptr);
	EXPECT_EQ(sizeof(size_t) * 4, b.length);
	EXPECT_TRUE(IsAligned(b.ptr, alignof(size_t)* 4));
	EXPECT_NO_FATAL_FAILURE(*reinterpret_cast<size_t*>(b.ptr) = 42ull);
}

TEST(LightInlineAllocator, Owns)
{
	LightInlineAllocator<64> a;
	auto const b1 = allocate<size_t>(a);
	EXPECT_TRUE(a.owns(b1));
	a.deallocate(b1);

	auto const b2 = a.allocate(sizeof(size_t) * 4, alignof(size_t)* 4);
	EXPECT_TRUE(a.owns(b2));
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

TEST(SegregateAllocator, SmallAllocate)
{
	SegregateAllocator<16, LightInlineAllocator<16>, MallocAllocator> a;

	auto const b = a.allocate(16);
	EXPECT_EQ(&a, b.ptr);
	EXPECT_EQ(16, b.length);
	EXPECT_NO_FATAL_FAILURE(*reinterpret_cast<size_t*>(b.ptr) = size_t{ 42 });

	a.deallocate(b);
}

TEST(SegregateAllocator, LargeAllocate)
{
	SegregateAllocator<16, LightInlineAllocator<16>, MallocAllocator> a;

	auto const b = a.allocate(32);
	EXPECT_NE(&a, b.ptr);
	EXPECT_EQ(32, b.length);
	EXPECT_NO_FATAL_FAILURE(*reinterpret_cast<size_t*>(b.ptr) = size_t{ 42 });

	a.deallocate(b);
}

TEST(SegregateAllocator, SmallAllocateAligned)
{
	SegregateAllocator<16, LightInlineAllocator<64>, MallocAllocator> a;

	auto const b = a.allocate(16, 16);
	EXPECT_TRUE(&a <= b.ptr && b.ptr <= &a + 8);
	EXPECT_EQ(16, b.length);
	EXPECT_NO_FATAL_FAILURE(*reinterpret_cast<size_t*>(b.ptr) = size_t{ 42 });

	a.deallocate(b);
}

TEST(SegregateAllocator, LargeAllocateAligned)
{
	SegregateAllocator<16, LightInlineAllocator<64>, MallocAllocator> a;

	auto const b = a.allocate(32, 16);
	EXPECT_FALSE(&a <= b.ptr && b.ptr <= &a + 8);
	EXPECT_EQ(32, b.length);
	EXPECT_NO_FATAL_FAILURE(*reinterpret_cast<size_t*>(b.ptr) = size_t{ 42 });

	a.deallocate(b);
}

TEST(SegregateAllocator, SmallOwns)
{
	SegregateAllocator<16, LightInlineAllocator<16>, MallocAllocator> a;

	auto const b = a.allocate(16);
	EXPECT_TRUE(a.owns(b));

	a.deallocate(b);
}

TEST(SegregateAllocator, LargeOwns)
{
	SegregateAllocator<16, LightInlineAllocator<16>, MallocAllocator> a;

	auto const b = a.allocate(32);
	EXPECT_TRUE(a.owns(b));

	a.deallocate(b);
}

static_assert(sizeof(SegregateAllocator<16, NullAllocator, MallocAllocator>) == 1, "!!!!");

static_assert(std::is_empty<SegregateAllocator<16, NullAllocator, MallocAllocator>>::value, "!!!?");
static_assert(StateSize<SegregateAllocator<16, NullAllocator, MallocAllocator>>::value == 0, "???!");

static_assert(equal_<StateSize<SegregateAllocator<16, NullAllocator, MallocAllocator>>, std::integral_constant<size_t, 0>>::value, "???");
static_assert(IsStatelessAllocator<SegregateAllocator<16, NullAllocator, MallocAllocator>>(), "Test fail on SegregateAllocator");