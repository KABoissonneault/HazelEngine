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