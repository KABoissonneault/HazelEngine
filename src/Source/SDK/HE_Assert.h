#pragma once

#include <exception>

namespace HE
{
	namespace Assert
	{
		enum class Response { Halt, Continue, Terminate, Exception };
		using Handler = Response(*) (const char* sCondition, const char* sMessage, const char* file, int line);

		// If you want to change how the assertions are handled, change the Handler
		// Takes the assert information as parameters (ex: if you want to show it to the user before taking a decision)
		// then returns a response on how the program should react
		Handler GetHandler();
		void SetHandler(Handler handler);

		class Exception : public std::exception
		{
		public:
			Exception(const std::string& sMessage) : m_sMessage(sMessage) {}
			Exception(std::string&& sMessage) : m_sMessage(sMessage) {}

			virtual const char* what() const override;

		private:
			std::string m_sMessage;
		};

		// Use the assert macros below, not this
		namespace Private
		{
			bool ReportFailure(const char* sCondition, const char* sFile, int line, const char* msg, ...);
		}
	}
}

#define ASSERTS_ENABLED 1

#if ASSERTS_ENABLED > 0

#define Assert_Msg_F(bCondition, sMsg, ...)															\
	do {																							\
		using namespace HE::Assert::Private;														\
		if( !(bCondition) ) {																		\
			if(ReportFailure(#bCondition, __FILE__, __LINE__, sMsg, __VA_ARGS__)) debug_break();	\
		}																							\
	} while (__LINE__ == -1, false)
#else
#define HE_ASSERT_MSG_F(bCondition, sMsg, ...) \
	do { (void)sizeof(bCondition); (void)sizeof(sMsg); (void)sizeof(__VA_ARGS__); } while(__LINE__ == -1, false)
#endif // ASSERTS_ENABLED


#define Assert_Msg(bCondition, sMsg) Assert_Msg_F((bCondition), (sMsg), "")
#define Assert(bCondition)	Assert_Msg_F((bCondition), "", "")		

// Contract enforcements
#define Expects(bCondition) Assert_Msg(bCondition, "Pre-condition fail")
#define Ensures(bCondition) Assert_Msg(bCondition, "Post-condition fail")