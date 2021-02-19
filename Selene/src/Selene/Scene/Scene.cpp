#include "slnpch.h"
#include "Scene.h"
#include "Actor.h"

namespace Selene
{
	Actor Scene::CreateActor(const std::string& name)
	{
		return Actor { m_Registry.create(), shared_from_this() };
	}

	void Scene::DestroyActor(Actor actor)
	{
		m_Registry.destroy(actor.GetActorID());
	}
}