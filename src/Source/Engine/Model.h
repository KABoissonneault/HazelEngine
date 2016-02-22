#pragma once

#include <vector>
#include <memory>


namespace HE
{
	class Entity;

	class Model
	{
	public:

		void Update(double dt);

		auto& GetEntities() noexcept { return m_cEntities; }
		auto const& GetEntities() const noexcept { return m_cEntities; }

	private:
		std::vector<std::unique_ptr<Entity>> m_cEntities;

	};

}