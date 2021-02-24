#pragma once

#include "Scene.h"
#include <entt/entt.hpp>

namespace Selene
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(entt::entity id, std::shared_ptr<Scene> scene);
	public:
		template<typename T, typename... Args>
		inline T& AddComponent(Args&&... args) { return m_Scene.lock()->GetRegistry().emplace<T>(m_ActorID, std::forward<Args>(args)...); } // perfect forwarding
		template<typename T>
		inline T& GetComponent() { return m_Scene.lock()->GetRegistry().get<T>(m_ActorID); }
	public:
		inline entt::entity GetActorID() const { return m_ActorID; }
	public:
		inline bool operator==(const Actor& other) const { return m_ActorID == other.m_ActorID && m_Scene.lock() == other.m_Scene.lock(); }
		inline bool operator!=(const Actor& other) const { return !(*this == other); }
	private:
		entt::entity m_ActorID = entt::null;
		std::weak_ptr<Scene> m_Scene;
	};
}