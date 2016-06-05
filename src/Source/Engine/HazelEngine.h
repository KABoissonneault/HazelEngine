#pragma once

#include <future>
#include <cstdint>

namespace HE
{
	using EngineVersion = std::uint32_t;
	using EngineVersionMajor = std::uint8_t;
	using EngineVersionMinor = std::uint8_t;
	using EngineVersionPatch = std::uint16_t;

	constexpr EngineVersion MakeVersion(EngineVersionMajor major, EngineVersionMinor minor, EngineVersionPatch patch) noexcept
	{
		return  (((major) << 24) | ((minor) << 16)  | (patch));
	}

	constexpr EngineVersionMajor GetMajor(EngineVersion v)
	{
		return v >> 24;
	}

	constexpr EngineVersionMinor GetMinor(EngineVersion v)
	{
		return v >> 16 & 0xFF;
	}

	constexpr EngineVersionPatch GetPatch(EngineVersion v)
	{
		return v & 0xFFFF;
	}
		
	namespace Test
	{
		constexpr auto testVersion = MakeVersion(1, 2, 24);
		static_assert(testVersion == 0x01020018, "EngineVersion Test fail");
		static_assert(GetMajor(testVersion) == 1, "EngineVersion Test fail");
		static_assert(GetMinor(testVersion) == 2, "EngineVersion Test fail");
		static_assert(GetPatch(testVersion) == 24, "EngineVersion Test fail");
	}
	

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