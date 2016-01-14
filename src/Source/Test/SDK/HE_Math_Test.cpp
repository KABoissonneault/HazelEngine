#include <gtest/gtest.h>

#include "HE_Math.h"

using namespace HE::Math;

static_assert(!IsPow2(0), "HE::Math::IsPow2 failed to pass test");
static_assert(IsPow2(1), "HE::Math::IsPow2 failed to pass test");
static_assert(IsPow2(2), "HE::Math::IsPow2 failed to pass test");
static_assert(IsPow2(1024), "HE::Math::IsPow2 failed to pass test");

static_assert(Min(2, 3) == 2, "HE::Math::Min failed to pass test");
static_assert(Min(2, 3, 5, 1) == 1, "HE::Math::Min failed to pass test");
static_assert(Min(2, 2.4f, 1.0) == 1.0, "HE::Math::Min failed to pass test");

static_assert(Max(2, 3) == 3, "HE::Math::Max failed to pass test");
static_assert(Max(2, 3, 5, 1) == 5, "HE::Math::Max failed to pass test");
static_assert(Max(2, 2.4f, 1.0) == 2.4f, "HE::Math::Max failed to pass test");

static_assert(RoundUpToMultipleOf(1, 4) == 4, "HE::Math::RoundUpToMultipleOf failed to pass test");
static_assert(RoundUpToMultipleOf(13, 9) == 18, "HE::Math::RoundUpToMultipleOf failed to pass test");
//static_assert(RoundUpToMultipleOf(1, -2) == 4, "HE::Math::RoundUpToMultipleOf failed to pass test"); // Should not compile