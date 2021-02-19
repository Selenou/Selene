#include "slnpch.h"
#include "Actor.h"

namespace Selene
{
	Actor::Actor(entt::entity id, std::shared_ptr<Scene> scene) 
		: m_ActorID(id), m_Scene(scene) 
	{
	}
}