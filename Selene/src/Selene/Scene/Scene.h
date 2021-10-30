#pragma once

#include "Selene/Core/Time.h"
#include <entt/entt.hpp>

class b2World;

namespace Selene
{
	class Actor;

	class Scene : public std::enable_shared_from_this<Scene>
	{
	public:
		~Scene();
	public:
		Actor CreateActor(const std::string& name);
		void DestroyActor(const Actor& actor);
	public:
		void InitPhysicsWorld2D();
		void UpdatePhysicsWorld2D(Timestep ts);
	public:
		inline entt::registry& GetRegistry() { return m_Registry; }
	private:
		entt::registry m_Registry;
		b2World* m_PhysicsWorld = nullptr;
	};
}