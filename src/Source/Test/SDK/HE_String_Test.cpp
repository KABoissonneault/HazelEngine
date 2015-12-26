#include <gtest/gtest.h>

#include "HE_String.h"

using namespace HE;
using namespace std::string_literals;

TEST(to_string, float_format)
{
	auto const sFormat = "%2.4f";
	auto const fValue = 2.415f;

	auto const nStringSize = snprintf(nullptr, 0, sFormat, fValue);
	std::string sFormatted(nStringSize + 1, '\0');
	snprintf(&sFormatted[0], nStringSize + 1, sFormat, fValue);
	sFormatted.resize(nStringSize);
	EXPECT_EQ(sFormatted, to_string(fValue, "2.4"));
}

TEST(to_string, double_format)
{
	auto const sFormat = "%2.4f";
	auto const fValue = 2.415;

	auto const nStringSize = snprintf(nullptr, 0, sFormat, fValue);
	std::string sFormatted(nStringSize + 1, '\0');
	snprintf(&sFormatted[0], nStringSize + 1, sFormat, fValue);
	sFormatted.resize(nStringSize);
	EXPECT_EQ(sFormatted, to_string(fValue, "2.4"));
}

TEST(HE_Format, NoFormat)
{
	ASSERT_EQ("Hello", Format("Hello"));
}

TEST(HE_Format, SimpleString)
{
	ASSERT_EQ("Hello World!", Format("Hello {0}!", "World"));
}

TEST(HE_Format, SimpleNumber)
{
	ASSERT_EQ("LMAO! 2CAT!!1", Format("LMAO! {0}CAT!!1", 2));
}

TEST(HE_Format, Repeated)
{
	ASSERT_EQ("mushi mushi, Jesus desu", Format("{0} {0}, Jesus desu", "mushi"));
}

TEST(HE_Format, MultipleArguments)
{
	ASSERT_EQ("The result of this test is 42", Format("The {0} of this {1} is {2}", "result", "test", 42));
}

TEST(HE_Format, FormatArgument)
{
	ASSERT_NO_THROW(Format("{0:.2}", 7.25f));
	EXPECT_EQ("7.25", Format("{0:.2}", 7.25f));
	EXPECT_EQ("7.2500", Format("{0:.4}", 7.25f));
}

TEST(HE_Format, MisorderedArguments)
{
	ASSERT_EQ("7.5 + 13.5 = 21", Format("{1:1.1} + {2:2.1} = {0}", 21, 7.5f, 13.5));
}