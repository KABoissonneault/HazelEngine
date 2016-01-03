#pragma once

#include <future>

namespace HE
{

	// Represents a game engine that wraps both a Model of a game and
	// a View of the Model
	// The Engine can be customized on construction
	// The Engine should be Run after being constructed. The Engine
	// will then run on its own and do its own thing, until told to stop or 
	// decides to stop

	// Ensures: Stops on destruction
	class Engine
	{
	public:
		Engine() noexcept = default;
		Engine(const std::vector<std::string>& Args);
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;
		void operator=(const Engine&) = delete;
		void operator=(Engine&&) = delete;
		~Engine();
		
		// Getting the future will block until the Engine has stopped running
		// Should only be called once on the object
		std::future<void> Run();

		// Thread-safe. Signals the Engine to stop running
		void Stop();

	private:
		std::atomic<bool> m_bShouldStop{false};
		bool m_bRunning{ false };
	};
}