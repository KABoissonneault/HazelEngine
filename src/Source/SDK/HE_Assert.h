#pragma once

#include <string>
#include <exception>
#include <debugbreak.h>

namespace HE
{
	namespace Assert
	{
		enum class Response { Halt, Continue, Terminate, Exception };
		using Handler = Response(*) (const std::string& sCondition, const std::string& sMessage, const std::string& file, int line);

		// If you want to change how the assertions are handled, change the Handler
		// Takes the assert information as parameters (ex: if you want to show it to the user before taking a decision)
		// then returns a response on how the program should react
		Handler GetHandler();
		void SetHandler(Handler handler);

		class Exception : public std::exception
		{
		public:
			template< typename String1, typename String2 >
			Exception(String1&& sCondition, const std::string& sMessage, String2&& sFile, int nLine) 
				: m_sCondition{ std::forward<String1>(sCondition) },  
				m_sMessage { FormatExceptionMessage(sCondition, sMessage, sFile, nLine) }, 
				m_sFile{ std::forward<String2>(sFile) }, m_nLine{ nLine } 
			{}

			virtual const char* what() const override;

			const std::string& GetCondition() const noexcept {
				return m_sCondition;
			}

			const std::string& GetMessage() const noexcept {
				return m_sMessage;
			}

			const std::string& GetFile() const noexcept {
				return m_sFile;
			}

			int GetLine() const noexcept {
				return m_nLine;
			}

		private:
			static std::string FormatExceptionMessage(const std::string& sCondition, const std::string& sMessage, const std::string& sFile, int nLine);

			std::string m_sCondition;
			std::string m_sMessage;
			std::string m_sFile;
			int m_nLine;
		};

		// Use the assert macros below, not this
		namespace Private
		{
			template< typename String1, typename String2, typename String3 >
			bool ReportFailure(String1&& sCondition, String2&& sMsg, String3&& sFile, int nLine)
			{
				auto const eResponse = GetHandler()(sCondition, sMsg, sFile, nLine);

				switch (eResponse)
				{
				case Response::Halt: return true;
				case Response::Terminate: std::terminate(); break;
				case Response::Exception: throw Exception{ std::forward<String1>(sCondition), std::forward<String2>(sMsg), std::forward<String3>(sFile), nLine }; break;
				case Response::Continue: break;
				}

				return false;
			}
		}
	}
}

#define ASSERTS_ENABLED 1

#if ASSERTS_ENABLED > 0

#ifdef ASSERT_MSG
#undef ASSERT_MSG
#endif
#define ASSERT_MSG(bCondition, sMsg)																\
	do {																							\
		using namespace HE::Assert::Private; using namespace std::string_literals;					\
		if( !(bCondition) ) {																		\
			if(ReportFailure(#bCondition, (sMsg), __FILE__, __LINE__)) debug_break();				\
		}																							\
	} while (__LINE__ == -1, false)
#else
#define Assert_Msg(bCondition, sMsg) \
	do { (void)sizeof(bCondition); (void)sizeof(sMsg); } while(__LINE__ == -1, false)
#endif // ASSERTS_ENABLED

#ifdef ASSERT
	#undef Assert
#endif
#define ASSERT(bCondition)	ASSERT_MSG((bCondition), "Assertion fail")		

#ifdef EXPECTS
	#undef EXPECTS
#endif
#ifdef ENSURES
	#undef ENSURES
#endif

// Contract enforcements
#define EXPECTS(bCondition) ASSERT_MSG(bCondition, "Pre-condition fail")
#define ENSURES(bCondition) ASSERT_MSG(bCondition, "Post-condition fail")