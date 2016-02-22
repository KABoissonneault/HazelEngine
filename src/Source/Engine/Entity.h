#pragma once

#include <cstdint>

namespace HE
{
	class Entity
	{
	public:

		auto GetGlobalUniqueID() const noexcept { return m_nGlobalUniqueID; }

	private:
		std::uint64_t m_nGlobalUniqueID;
	};
}