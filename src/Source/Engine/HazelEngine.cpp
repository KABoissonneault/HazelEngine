#include "HazelEngine.h"

#include "HE_Assert.h"
#include "HE_String.h"

namespace HE
{
	Engine::Engine(const std::vector<std::string>& args)
	{

	}

	Engine::~Engine() { Stop(); }

	std::future<void> Engine::Run()
	{
		EXPECTS(!m_bRunning);

		m_bRunning = true;

		std::packaged_task<void()> engineRun([this]() {
			using namespace std::literals::chrono_literals;

			Log("Hello, this is HazelEngine");

			auto i = 0;
			while (!m_bShouldStop) 
			{ 
				std::this_thread::sleep_for(100ms); 
				++i;
				if (i > 100)
				{
					Log("HazelEngine got bored doing nothing, it will now stop");
					Stop();
					break;
				}
			}

			Log("HazelEngine has stopped");
			return;
		});
		auto futEngineEnd = engineRun.get_future();

		std::thread task_td(std::move(engineRun));
		task_td.detach();

		return futEngineEnd;
	}

	void Engine::Stop()
	{
		m_bShouldStop = true;
	}
}