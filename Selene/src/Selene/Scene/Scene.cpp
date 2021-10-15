#include "slnpch.h"
#include "Scene.h"
#include "Actor.h"
#include "Components/NameComponent.h"

namespace Selene
{
	Actor Scene::CreateActor(const std::string& name)
	{
		 Actor actor { m_Registry.create(), shared_from_this() };
		 actor.AddComponent<NameComponent>(name);
		 return actor;
	}

	void Scene::DestroyActor(const Actor& actor)
	{
		m_Registry.destroy(actor.GetActorID());
	}
}