#include <stdio.h>

#include "gtest/gtest.h"


#include "HE_String.h"
#include "HE_Assert.h"
#include <debugbreak.h>

HE::Assert::Response TestAssertHandler(const std::string& sCondition, const std::string& sMessage, const std::string& file, int line)
{
	// Use exceptions for asserts, so we can test for throws
	return HE::Assert::Response::Exception;
}

GTEST_API_ int main(int argc, char **argv) {
	printf("Running main() from test_main.cpp\n");
	testing::InitGoogleTest(&argc, argv);

	HE::Assert::SetHandler(&TestAssertHandler);

	auto const ret = RUN_ALL_TESTS();
	//debug_break();
	return ret;
}
