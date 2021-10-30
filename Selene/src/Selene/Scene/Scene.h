#pragma once

#include <entt/entt.hpp>

namespace Selene
{
	class Actor;

	class Scene : public std::enable_shared_from_this<Scene>
	{
	public:
		Scene() = default;
	public:
		Actor CreateActor(const std::string& name);
		void DestroyActor(const Actor& actor);
	public:
		inline entt::registry& GetRegistry() { return m_Registry; }
	private:
		entt::registry m_Registry;
	};
}