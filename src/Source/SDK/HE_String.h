#pragma once

#include <gsl.h>
#include <string>
#include <cstdarg>
#include <typeinfo>

#include "HE_Assert.h"
#include "TMP_Helper.h"

// Utility function that calls the right variadic formatting functions and returns an RAII string
std::string CStringFormat(const char* sFormat, va_list args);
std::string CStringFormat(const char* sFormat, ...);

// Default to_string functions
using std::to_string;
using gsl::to_string;
std::string to_string(const std::exception& e);
std::string to_string(void* p);

inline std::string& to_string(std::string& s) { return s; }
inline std::string to_string(std::string&& s) { return s; }
inline const std::string& to_string(const std::string& s) { return s; }
inline std::string to_string(const char* s) { return{ s }; }

// Built-in type formats specifiers
// Can be used to format a built-in type to a string with a special format.
// Use HasFormatSpecifier<T> to test statically (ex: static_assert(...)) if a type supports
// a format specifier
// The format specifier is in the same format as printf (http://en.cppreference.com/w/cpp/io/c/fprintf), 
// except that the conversion format specifier (aka the last letter[s]) can be ignored, in which case the
// default specifier for the type will be used (ex: d for int, u for unsigned, f for float, etc...)
// On top of that, for long sized types, only the conversion specifier without the argument type can be
// supplied. For example, for unsigned long, the format could be " .4o", which will be converted to
// " .4ol". Supplying " .4ol" itself would also work
std::string to_string(int val, const std::string& sFormat); // Defaults to %[sFormat]d
std::string to_string(unsigned int val, const std::string& sFormat); // Defaults to %[sFormat]u
std::string to_string(long val, const std::string& sFormat); // Defaults to %[sFormat]dl
std::string to_string(unsigned long val, const std::string& sFormat); // Defaults to %[sFormat]ul
std::string to_string(long long val, const std::string& sFormat); // Defaults to %[sFormat]dll
std::string to_string(unsigned long long val, const std::string& sFormat); // Defaults to %[sFormat]ull
std::string to_string(float val, const std::string& sFormat); // Defaults to %[sFormat]f
std::string to_string(double val, const std::string& sFormat); // Defaults to %[sFormat]f
std::string to_string(long double val, const std::string& sFormat); // Defaults to %[sFormat]fL
std::string to_string(void* val, const std::string& sFormat); // Defaults to %[sFormat]p


namespace HE
{
	namespace Private
	{
		template<class T>
		using try_format = decltype(to_string(std::declval<T>()));

		template<class T>
		using has_format = has_op < T, try_format >;
		
		template<class T>
		using try_format_specifier = decltype(to_string(std::declval<T>(), std::declval<std::string>()));

		template<class T>
		using has_format_specifier = has_op<T, try_format_specifier >;

		template< typename Arg >
		std::string FormatIthArgN(size_t i, size_t n, Arg&& arg)
		{
			ASSERT_MSG(i == n, "String format token number was higher than the number of arguments");
			return to_string(std::forward<Arg>(arg));
		}

		template< typename Arg1, typename... Args >
		std::string FormatIthArgN(size_t i, size_t n, Arg1&& arg, Args&&... args)
		{
			if (i == n)
			{
				return to_string(std::forward<Arg1>(arg));
			}
			else
			{
				return FormatIthArgN(i, n + 1, std::forward<Args>(args)...);
			}
		}

		template< typename Arg>
		auto FormatIthArgFN(size_t i, size_t n, const std::string& format, Arg&& arg)
			-> std::enable_if_t<has_format_specifier<Arg>::value, std::string>
		{
			ASSERT_MSG(i == n, "String format token number was higher than the number of arguments");
			return to_string(std::forward<Arg>(arg), format);
		}

		template< typename Arg >
		auto FormatIthArgFN(size_t i, size_t n, const std::string& format, Arg&& arg)
			-> std::enable_if_t<!has_format_specifier<Arg>::value, std::string>
		{
			ASSERT_MSG(false , "A format specifier was supplied with type "s + typeid(Arg).name() + " which that does not support it");
			return "";
		}

		template< typename Arg1, typename... Args >
		std::string FormatIthArgFN(size_t i, size_t n, const std::string& format, Arg1&& arg, Args&&... args)
		{
			if (i == n)
			{
				return FormatIthArgFN(i, n, format, std::forward<Arg1>(arg));
			}
			else
			{
				return FormatIthArgFN(i, n + 1, format, std::forward<Args>(args)...);
			}
		}

		template< typename... Args >
		std::string FormatIthArg(size_t i, Args&&... args)
		{
			return FormatIthArgN(i, 0, std::forward<Args>(args)...);
		}

		template< typename... Args >
		std::string FormatIthArgF(size_t i, const std::string& format, Args&&... args)
		{
			return FormatIthArgFN(i, 0, format, std::forward<Args>(args)...);
		}
	}

	// Can be used in statically evaluated context to test if the type can be formatted
	// to a string and formatted with a format specifier
	template< class... T >
	constexpr bool HasFormat()
	{
		return and_<Private::has_format<T>...>::value;
	}

	template< class... T >
	constexpr bool HasFormatSpecifier()
	{
		return and_<Private::has_format_specifier<T>...>::value;
	}

	// Form: Format(sFormat, args...) -> sFormatted
	// Formats the string according to format tokens and arguments
	// Format token have the format "{i}" or "{i:xxxx}", where i is a 0-based argument index to be
	// converted to string or the character '_', which means next argument (starting at 0)
	// "xxxx" is a format string to be passed to the argument 
	// 
	// In order to be featured in a format token, an argument must have a "to_string" function available
	// either in the global namespace or in the same scope as the type of the argument, which
	// will be found through ADL
	// To have a format specifier, the argument must have a "to_string" which takes a string as
	// second argument
	// You can test for both of these conditions statically with HasFormat<T>() and HasFormatSpecifier<T>()

    // Example: Format("{0:dd-mm-yyyy}", date) -> to_string(date, "dd-mm-yyyy")

	// Pre-condition: The biggest index in the format string must be smaller than
	// the number of arguments, and indices can't be negative
	inline std::string Format(const std::string& sFormat)
	{
		return sFormat;
	}

	template< typename... Args>
	std::string Format(const std::string& sFormat, Args&&... args)
	{
		static_assert(HasFormat<Args...>(), "An argument cannot be formatted (HasFormat returns false)");

		using namespace HE::Private;

		std::string sOutput;
		size_t nNextArg = 0;
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
				i = endToken;
				ASSERT_MSG(endToken != std::string::npos, "Token error in string format \"" + sFormat + "\"");

				// Find the index token inside the whole token
				auto const sFormatToken = sFormat.substr(posToken + 1, (endToken - 1) - posToken);
				auto const nSpecifierSentinel = sFormatToken.find_first_of(':');
				auto const sIndexToken = [sFormatToken, nSpecifierSentinel]() {
					if (nSpecifierSentinel == std::string::npos)
					{
						return sFormatToken;
					}
					else
					{
						return sFormatToken.substr(0, nSpecifierSentinel);
					}
				}();
				
				// Find the index of the current arg for this token
				auto const argPos = [sIndexToken, nNextArg]() -> size_t {
					if (sIndexToken == "_")
					{
						return nNextArg;
					}
					else
					{
						return std::stoi(sIndexToken);
					}
				}();
				nNextArg = argPos + 1;
				
				// Add the formatted argument to the output
				if (nSpecifierSentinel == std::string::npos)
				{	
					sOutput += FormatIthArg(argPos, std::forward<Args>(args)...);
				}
				else
				{
					auto const sSpecifierToken = sFormatToken.substr(nSpecifierSentinel + 1);
					sOutput += FormatIthArgF(argPos, sSpecifierToken, std::forward<Args>(args)...);
				}
			}
		}

		return sOutput;
	}
	
	// Thread-safe logging
	void Log(const std::string& sMsg) noexcept;
	void LogError(const std::string& sMsg) noexcept;

	template< typename... Args>
	void Log(const std::string& sFormat, Args&&... args)
	{
		Log(Format(sFormat, std::forward<Args>(args)...));
	}

	template< typename... Args>
	void LogError(const std::string& sFormat, Args&&... args)
	{
		LogError(Format(sFormat, std::forward<Args>(args)...));
	}
}