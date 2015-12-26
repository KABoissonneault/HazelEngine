#include "stdafx.h"
#include "HE_String.h"

#include <cstdarg>

std::string CStringFormat(const char* const sFormat, va_list args)
{
	auto const nSize = vsnprintf(nullptr, 0, sFormat, args);
	auto buffer = std::string( nSize + 1, '\0' );
	auto const nRes = vsnprintf(&buffer[0], nSize + 1, sFormat, args);

	Assert(nRes == nSize);

	return buffer;
}

std::string CStringFormat(const char* const sFormat, ...)
{
	va_list args;
	va_start(args, sFormat);
	auto const buffer = CStringFormat(sFormat, args);
	va_end(args);

	return buffer;
}

std::string to_string(const std::exception& e)
{
	return{ e.what() };
}

namespace
{
	template< class T >
	std::string to_string_impl(T arg, const std::string& sFormat)
	{
		using namespace std::string_literals;

		auto const nStringSize = snprintf(nullptr, 0, sFormat.c_str(), arg);
		std::string sOutput(nStringSize + 1, '\0');
		auto const nResult = snprintf(&sOutput[0], nStringSize + 1, sFormat.c_str(), arg);
		sOutput.resize(nStringSize);
		Assert(nStringSize == nResult);

		return sOutput;
	}
}

std::string to_string(double f, const std::string& sFormat, const std::string& sStyle /* ="f" */)
{
	return to_string_impl(f, "%" + sFormat + sStyle);
}

std::string to_string(long double f, const std::string& sFormat, const std::string& sStyle /* ="f" */)
{
	return to_string_impl(f, "%" + sFormat + sStyle + "L");
}