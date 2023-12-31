#include "physics.h"

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>

#include <ecs/components.h>

namespace Teapot
{
    b2BodyType RigidbodyTypeTob2BodyType(RigidbodyType type)
    {
        switch(type)
        {
        case RigidbodyType::Static:     return b2_staticBody;
        case RigidbodyType::Dynamic:    return b2_dynamicBody;
        case RigidbodyType::Kinematic:  return b2_kinematicBody;
        
        default:
            assert(false);
            return b2_staticBody;
        }
    }

    void Physics::Start(Scene& scene)
    {
        b2Vec2 gravity(0.0f, -10.0f);
        m_PhysicWorld = std::make_shared<b2World>(gravity);
    }

    void Physics::Update(Scene &scene, float deltaTime)
    {
        constexpr int32_t velocityIterations = 8;
        constexpr int32_t positionIterations = 3;
        m_PhysicWorld->Step(deltaTime, velocityIterations, positionIterations);
        
        auto view =  scene.GetRegistry().view<const RigidbodyComponent, TransformComponent>();
        view.each([this, &scene](auto entity, auto& rigidbodyCmp, auto& transformCmp)
        {
            if (rigidbodyCmp.PhysicBody == nullptr)
            {
                Entity e{&scene, entity};
                CreatePhysicBody(e);
            }

            const b2Body* body = static_cast<b2Body*>(rigidbodyCmp.PhysicBody);
            const b2Vec2& position = body->GetPosition();
            transformCmp.Position = Vector2{ position.x, position.y };
            transformCmp.Rotation = body->GetAngle();
        });
    }

    void Physics::Stop(Scene &scene)
    {
        m_PhysicWorld.reset();
    }

    void Physics::CreatePhysicBody(Entity entity)
    {
        if (!entity.HasComponent<RigidbodyComponent>())
            return;

        auto& rigidbodyCmp = entity.GetComponent<RigidbodyComponent>();
        auto& transformCmp = entity.GetComponent<TransformComponent>();

        b2BodyDef bodyDefinition;
        bodyDefinition.type = RigidbodyTypeTob2BodyType(rigidbodyCmp.Type);
        bodyDefinition.position.Set(transformCmp.Position.x, transformCmp.Position.y);
        bodyDefinition.fixedRotation = rigidbodyCmp.FixedRotation;
        
        b2Body* body = m_PhysicWorld->CreateBody(&bodyDefinition);
        rigidbodyCmp.PhysicBody = body;

        if (entity.HasComponent<BoxColliderComponent>())
        {
            auto& boxColliderCmp = entity.GetComponent<BoxColliderComponent>();

            b2PolygonShape shape;
            shape.SetAsBox(boxColliderCmp.HalfExtents.x, boxColliderCmp.HalfExtents.y);

            b2FixtureDef fixtureDefinition;
            fixtureDefinition.shape = &shape;
            fixtureDefinition.density = boxColliderCmp.Density;
            fixtureDefinition.friction = boxColliderCmp.Friction;
            fixtureDefinition.restitution = boxColliderCmp.Restitution;
            fixtureDefinition.restitutionThreshold = boxColliderCmp.RestitutionThreshold;

            boxColliderCmp.PhysicFixture = body->CreateFixture(&fixtureDefinition);
        }
    }
    
    void Physics::OnEntityDestroyed(Entity e)
    {
        if (!e.HasComponent<RigidbodyComponent>())
            return;

        auto& rigidbodyCmp = e.GetComponent<RigidbodyComponent>();
        b2Body* body = static_cast<b2Body*>(rigidbodyCmp.PhysicBody);
        m_PhysicWorld->DestroyBody(body);
    }
}
