#include "stdafx.h"
#include "HE_Assert.h"

#include <iostream>
#include <cstdarg>
#include <vector>

namespace HE
{
	namespace Assert
	{
		namespace
		{
			Response DefaultHandler(char const* const psCondition, char const* const psMsg, char const* const psFile, int const nLine)
			{
				std::cout << "[" << psFile << "(" << nLine << ")] Assert failure ("
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
			return m_sMessage.c_str();
		}

		namespace Private
		{
			bool ReportFailure(const char* psCondition, const char* psFile, int nLine, const char* psMsg, ...)
			{
				va_list args;
				va_start(args, psMsg);
				auto const sMessage = CStringFormat(psMsg, args);
				va_end(args);

				auto const eResponse = s_pAssertHandler(psCondition, sMessage.c_str(), psFile, nLine);

				switch (eResponse)
				{
				case Response::Halt: return true;
				case Response::Terminate: std::terminate(); break;
				case Response::Exception: throw Exception{ sMessage }; break;
				case Response::Continue: break;
				}

				return false;
			}
		}
	}
}
