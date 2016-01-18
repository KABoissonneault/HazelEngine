#include "HE_Assert.h"

#include <iostream>
#include <cstdarg>
#include <vector>

#include "HE_String.h"

namespace HE
{
	namespace Assert
	{
		namespace
		{
			Response DefaultHandler(const std::string& psCondition, const std::string& psMsg, const std::string& psFile, int const nLine)
			{
				std::cerr << "[" << psFile << "(" << nLine << ")] Assert failure ("
					<< psCondition << "): "
					<< psMsg
					<< std::endl;

				return Response::Halt;
			}

			Handler s_pAssertHandler = DefaultHandler;
		}

		Handler GetHandler()
		{
			return s_pAssertHandler;
		}

		void SetHandler(Handler pHandler)
		{
			s_pAssertHandler = pHandler;
		}

		const char* Exception::what() const
		{
			return GetMessage().c_str();
		}

		std::string Exception::FormatExceptionMessage(const std::string& sCondition, const std::string& sMessage, const std::string& sFile, int nLine)
		{
			return "[" + sFile + " (" + ::to_string(nLine) + ")] Assert failure exception: (" + sCondition + ") " + sMessage;
		}
	}
}
