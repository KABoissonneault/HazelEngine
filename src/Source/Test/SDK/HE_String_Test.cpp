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
	ASSERT_EQ(sFormatted, to_string(fValue, "2.4"));
}

TEST(to_string, double_format)
{
	auto const sFormat = "%2.4f";
	auto const fValue = 2.415;

	auto const nStringSize = snprintf(nullptr, 0, sFormat, fValue);
	std::string sFormatted(nStringSize + 1, '\0');
	snprintf(&sFormatted[0], nStringSize + 1, sFormat, fValue);
	sFormatted.resize(nStringSize);
	ASSERT_EQ(sFormatted, to_string(fValue, "2.4"));
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

TEST(HE_Format, NextArg)
{
	ASSERT_EQ("Can you recognize those memes?", Format("Can you recognize those {_}?", "memes"));
}

TEST(HE_Format, NextArgMultiple)
{
	ASSERT_EQ("I wish I could take this testing seriously", 
		Format("{_} wish I could take this {_} {_}", "I", "testing", "seriously"));
}

TEST(HE_Format, NextArgOffset)
{
	ASSERT_EQ("It's currently 42 degrees Fahrenheit outside in this January 3rd. Oh btw forgot Hello",
		Format("It's currently {1} degrees {_} outside in this {3} {_}rd. Oh btw forgot {0}", "Hello", 42, "Fahrenheit", "January", 3));
}

TEST(HE_Format, Repeated)
{
	ASSERT_EQ("mushi mushi, Jesus desu", Format("{0} {0}, Jesus desu", "mushi"));
}

TEST(HE_Format, MultipleArguments)
{
	ASSERT_EQ("The result of this test is 42", Format("The {0} of this {1} is {2}", "result", "test", 42));
}

TEST(HE_Format, FormatWorks)
{
	ASSERT_NO_THROW(Format("{0:.2}", 7.25f));
}

TEST(HE_Format, FormatArgument)
{
	EXPECT_EQ("7.25", Format("{0:.2}", 7.25f));
	EXPECT_EQ("7.2500", Format("{0:.4}", 7.25f));
}

TEST(HE_Format, NextArgFormat)
{
	ASSERT_EQ("Pi is kind of like 3.14", Format("Pi is kind of like {_:.2}", 3.1415f));
}

TEST(HE_Format, MisorderedArguments)
{
	ASSERT_EQ("7.5 + 13.5 = 21", Format("{1:1.1} + {2:2.1} = {0}", 21, 7.5f, 13.5));
}