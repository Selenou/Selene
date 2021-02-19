#pragma once

#include "Scene.h"
#include <entt/entt.hpp>

namespace Selene
{
	class Actor
	{
	public:
		Actor(entt::entity id, std::shared_ptr<Scene> scene);
	public:
		template<typename T, typename... Args>
		inline T& AddComponent(Args&&... args) { return m_Scene.lock()->GetRegistry().emplace<T>(m_ActorID, std::forward<Args>(args)...); } // perfect forwarding
	public:
		inline entt::entity GetActorID() const { return m_ActorID; }
	private:
		entt::entity m_ActorID = entt::null;
		std::weak_ptr<Scene> m_Scene;
	};
}