#include "stdafx.h"
#include "HE_String.h"

#include <mutex>
#include <cstdarg>
#include <cctype>

std::string CStringFormat(const char* const sFormat, va_list args)
{
	auto const nSize = vsnprintf(nullptr, 0, sFormat, args);
	auto buffer = std::string( nSize + 1, '\0' );
	auto const nRes = vsnprintf(&buffer[0], nSize + 1, sFormat, args);

	ASSERT(nRes == nSize);

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

		auto const sFormatSpecifier = "%" + sFormat;
		auto const nStringSize = snprintf(nullptr, 0, sFormatSpecifier.c_str(), arg);
		std::string sOutput(nStringSize + 1, '\0');
		auto const nResult = snprintf(&sOutput[0], nStringSize + 1, sFormatSpecifier.c_str(), arg);
		sOutput.resize(nStringSize);
		ASSERT(nStringSize == nResult);

		return sOutput;
	}

	template< class T >
	std::string to_string_default(T val, const std::string& sFormat, const char sDefaultSpecifier[])
	{
		if (std::isalpha(*rbegin(sFormat)))
		{
			return to_string_impl(val, sFormat);
		}
		else
		{
			return to_string_impl(val, sFormat + sDefaultSpecifier);
		}
	}

	template< class T >
	std::string to_string_default(T val, const std::string& sFormat, const char sDefaultSpecifier[], const std::string& sDefaultArgumentType)
	{
		auto const lastFormatChar = *rbegin(sFormat);
		if (lastFormatChar == *crbegin(sDefaultArgumentType))
		{
			return to_string_impl(val, sFormat);
		}
		else if (std::isalpha(lastFormatChar))
		{
			return to_string_impl(val, sFormat + sDefaultArgumentType);
		}
		else
		{
			return to_string_impl(val, sFormat + sDefaultSpecifier);
		}
	}
}

std::string to_string(int val, const std::string& sFormat)
{
	return to_string_default(val, sFormat, "d");
}

std::string to_string(unsigned int val, const std::string& sFormat)
{
	return to_string_default(val, sFormat, "u");
}

std::string to_string(long val, const std::string& sFormat)
{
	return to_string_default(val, sFormat, "dl", "l");
}

std::string to_string(unsigned long val, const std::string& sFormat)
{
	return to_string_default(val, sFormat, "ul", "l");
}

std::string to_string(long long val, const std::string& sFormat)
{
	return to_string_default(val, sFormat, "dll", "ll");
}

std::string to_string(unsigned long long val, const std::string& sFormat)
{
	return to_string_default(val, sFormat, "ull", "ll");
}

std::string to_string(float f, const std::string& sFormat)
{
	return to_string_default(f, sFormat, "f");
}


std::string to_string(double f, const std::string& sFormat)
{
	return to_string_default(f, sFormat, "f");
}

std::string to_string(long double f, const std::string& sFormat)
{
	return to_string_default(f, sFormat, "fL");
}

namespace HE
{
	namespace
	{
		std::mutex s_mutLog;
		std::mutex s_mutLogError;
	}

	void Log(const std::string& sMessage) noexcept
	{
		try
		{
			std::lock_guard<std::mutex> lock{ s_mutLog };
			std::puts(sMessage.c_str());
		}
		catch (const std::system_error& e)
		{
			// Desperate attempt at logging the exception despite the lack of lock
			LogError("Error while attempting to log [" + sMessage + "]. The returned error was " + e.what());
		}
	}

	void LogError(const std::string& sMessage) noexcept
	{
		try
		{
			std::lock_guard<std::mutex> lock{ s_mutLog };
			std::fputs((sMessage + "\n").c_str(), stderr);
		}
		catch (const std::system_error& e)
		{
			// Desperate attempt at logging the exception despite the lack of lock
			std::fputs(("Error while attempting to log [" + sMessage + "]. The returned error was " + e.what()).c_str(), stderr);
		}
	}
}