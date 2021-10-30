#include "slnpch.h"
#include "Scene.h"
#include "Actor.h"
#include "Components/Components.h"

// Box2D
#include <box2d/b2_world.h>
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"

namespace Selene
{
	Scene::~Scene()
	{
		if (m_PhysicsWorld)
			delete m_PhysicsWorld;
	}

	Actor Scene::CreateActor(const std::string& name)
	{
		 Actor actor { m_Registry.create(), shared_from_this() };
		 actor.AddComponent<NameComponent>(name);
		 actor.AddComponent<TransformComponent>();
		 return actor;
	}

	void Scene::DestroyActor(const Actor& actor)
	{
		m_Registry.destroy(actor.GetActorID());
	}

	void Scene::InitPhysicsWorld2D()
	{
		m_PhysicsWorld = new b2World({ 0.0f, -9.8f });

		// TEST GROUND
		b2BodyDef bodyDefff;
		bodyDefff.type = b2_staticBody;
		bodyDefff.position.Set(0, -300);
		b2Body* bodyfff = m_PhysicsWorld->CreateBody(&bodyDefff);
		b2PolygonShape dynamicBoxfff;
		dynamicBoxfff.SetAsBox(1000.0f, 10.0f);
		b2FixtureDef fixtureDefff;
		fixtureDefff.shape = &dynamicBoxfff;
		fixtureDefff.density = 1.0f;
		fixtureDefff.friction = 0.3f;
		bodyfff->CreateFixture(&fixtureDefff);

		auto rgbdView = m_Registry.view<Rigidbody2DComponent>();
		for (auto a : rgbdView)
		{
			Actor actor = { a, shared_from_this() };
			auto& transform = actor.GetComponent<TransformComponent>();
			auto& rb2d = actor.GetComponent<Rigidbody2DComponent>();

			b2BodyDef bodyDef;
			if (rb2d.Type == Rigidbody2DComponent::BodyType::Static)
			{
				bodyDef.type = b2_staticBody;
			}
			else if (rb2d.Type == Rigidbody2DComponent::BodyType::Dynamic)
			{
				bodyDef.type = b2_dynamicBody;
			}
			else
			{
				bodyDef.type = b2_kinematicBody;
			}

			bodyDef.position.Set(transform.Position.x, transform.Position.y);
			bodyDef.angle = transform.Rotation.z;

			b2Body* body = m_PhysicsWorld->CreateBody(&bodyDef);
			body->SetFixedRotation(rb2d.FixedRotation);
			rb2d.RuntimeBody = body;

			//bullshit
			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox(1.0f, 1.0f);
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;
			fixtureDef.density = 1.0f;
			fixtureDef.friction = 0.3f;
			body->CreateFixture(&fixtureDef);
		}
	}

	void Scene::UpdatePhysicsWorld2D(Timestep ts)
	{
		const int32_t velocityIterations = 8;
		const int32_t positionIterations = 3;

		m_PhysicsWorld->Step(ts, velocityIterations, positionIterations);

		auto view = m_Registry.view<Rigidbody2DComponent>();

		for (auto a : view)
		{
			Actor actor = { a, shared_from_this() };
			auto& transform = actor.GetComponent<TransformComponent>();
			auto& rb2d = actor.GetComponent<Rigidbody2DComponent>();

			b2Body* body = (b2Body*)rb2d.RuntimeBody;
			const auto& position = body->GetPosition();
			transform.Position.x = position.x;
			transform.Position.y = position.y;
			transform.Rotation.z = body->GetAngle();
		}
	}
}