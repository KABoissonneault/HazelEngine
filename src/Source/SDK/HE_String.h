#pragma once

#include <gsl.h>
#include <string>
#include <cstdarg>
#include <typeinfo>

#include "HE_Assert.h"

std::string CStringFormat(const char* sFormat, va_list args);
std::string CStringFormat(const char* sFormat, ...);

using std::to_string;
using gsl::to_string;
std::string to_string(const std::exception& e);
inline std::string& to_string(std::string& s) { return s; }
inline std::string to_string(std::string&& s) { return s; }
inline std::string to_string(const char* s) { return{ s }; }
std::string to_string(double f, const std::string& sFormat, const std::string& style = "f");
std::string to_string(long double f, const std::string& sFormat, const std::string& style = "f");

namespace HE
{
	namespace Private
	{
		template< typename... Args >
		std::string FormatIthArg(size_t i, Args... args)
		{
			return FormatIthArgN(i, 0, args...);
		}

		template< typename Arg >
		std::string FormatIthArgN(size_t i, size_t n, Arg arg)
		{
			Assert_Msg(i == n, "String format token number was higher than the number of arguments");
			return to_string(arg);
		}

		template< typename Arg1, typename... Args >
		std::string FormatIthArgN(size_t i, size_t n, Arg1 arg, Args... args)
		{
			if (i == n)
			{
				return to_string(arg);
			}
			else
			{
				return FormatIthArgN(i, n + 1, args...);
			}
		}

		template< typename... Args >
		std::string FormatIthArgF(size_t i, const std::string& format, Args... args)
		{
			return FormatIthArgFN(i, 0, format, args...);
		}

		template<class T>
		using try_format_specifier = decltype(to_string(std::declval<T>(), std::declval<std::string>()));

		template<class T, template<class> class Op, class = std::void_t<>>
		struct is_valid : std::false_type {};

		template<class T, template<class> class Op>
		struct is_valid<T, Op, std::void_t<Op<T>>> : std::true_type {};

		template<class T>
		using has_format_specifier = is_valid<T, try_format_specifier>;

		template< typename Arg>
		auto FormatIthArgFN(size_t i, size_t n, const std::string& format, Arg arg)
			-> std::enable_if_t<has_format_specifier<Arg>::value, std::string>
		{
			Assert_Msg(i == n, "String format token number was higher than the number of arguments");
			return to_string(arg, format);
		}

		template< typename Arg >
		auto FormatIthArgFN(size_t i, size_t n, const std::string& format, Arg arg)
			-> std::enable_if_t<!has_format_specifier<Arg>::value, std::string>
		{
			Assert_Msg(false , "A format specifier was supplied with type "s + typeid(Arg).name() + " which that does not support it");
			return "";
		}

		template< typename Arg1, typename... Args >
		std::string FormatIthArgFN(size_t i, size_t n, const std::string& format, Arg1 arg, Args... args)
		{
			if (i == n)
			{
				return FormatIthArgFN(i, n, format, arg);
			}
			else
			{
				return FormatIthArgFN(i, n + 1, format, args...);
			}
		}
	}

	

	// Form: Format(sFormat, args...) -> sFormatted
	// Formats the string according to format tokens and arguments
	// Format token have the format "{i}" or "{i:xxxx}", where i is a 0-based argument index to be
	// converted to string, and "xxxx" is a format string to be passed to the argument 
    // Example: Format("{0:dd-mm-yyyy}", date) -> to_string(date, "dd-mm-yyyy")

	// Pre-condition: The number of arguments supplied with the format string must be equal to the 
	// greatest index referred by a token plus 1 ({2} -> 3 arguments)
	inline std::string Format(const std::string& sFormat)
	{
		return sFormat;
	}

	template< typename... Args>
	std::string Format(const std::string& sFormat, Args... args)
	{
		using namespace std::literals::string_literals;
		using namespace HE::Private;

		std::string sOutput;
		for (size_t i = 0; i < sFormat.size(); ++i)
		{
			// Find the next format token
			auto const posToken = sFormat.find_first_of('{', i);

			// Add to the output all the characters up until the next format token (or the end)
			// and process the format token if necessary
			if (posToken == std::string::npos)
			{
				sOutput += sFormat.substr(i);
				break;
			}
			// The sequence "\{" is not a token start, so we continue as if it was a normal character
			else if (posToken != 0 && sFormat[posToken - 1] == '\\')
			{
				sOutput += sFormat.substr(i, posToken - i);
				i = posToken;
				continue;
			}
			// Otherwise, we have a format token
			else
			{
				sOutput += sFormat.substr(i, posToken - i); // Add everything before the token

				auto const endToken = sFormat.find_first_of('}', posToken);
				Assert_Msg(endToken != std::string::npos, "Token error in string format \""s + sFormat + "\""s);

				auto const formatToken = sFormat.substr(posToken + 1, (endToken - 1) - posToken);
				auto const argSentinel = formatToken.find_first_of(':');
				if (argSentinel == std::string::npos)
				{
					auto const argPos = std::stoi(formatToken);
					sOutput += FormatIthArg(argPos, args...);
				}
				else
				{
					auto const argPos = std::stoi(formatToken.substr(0, argSentinel));
					sOutput += FormatIthArgF(argPos, formatToken.substr(argSentinel + 1), args...);
				}

				i = endToken;
			}
		}

		return sOutput;
	}
	void Log(const std::string& sMsg);
	template< typename... Args>
	void Log(const std::string& sFormat, Args... args)
	{
		Log(Format(sFormat, args));
	}
}