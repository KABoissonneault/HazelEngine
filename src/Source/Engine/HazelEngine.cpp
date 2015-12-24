#include "stdafx.h"

#include "HazelEngine.h"

namespace HE
{
	Engine::Engine(const std::vector<std::string>& args)
	{

	}

	Engine::~Engine() { Stop(); }

	std::future<void> Engine::Run()
	{
		Expects(!m_bRunning);

		m_bRunning = true;

		std::packaged_task<void()> engineRun([this]() {
			using namespace std::literals::chrono_literals;

			std::cout << "Hello, this is HazelEngine" << std::endl;

			auto i = 0;
			while (!m_bShouldStop) 
			{ 
				std::this_thread::sleep_for(1s); 
				++i;
				if (i > 10)
				{
					std::cout << "HazelEngine got bored doing nothing, it will now stop" << std::endl;
					Stop();
					break;
				}
			}

			std::cout << "HazelEngine has stopped" << std::endl;
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