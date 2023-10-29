#pragma once
#include <string>
#include <raylib.h>

namespace Teapot
{
    class Entity;
    
    struct UUIDComponent
    {
        int64_t UUID;
    };

    struct NameComponent
    {
        std::string Name;
    };

    struct TransformComponent
    {
        Vector2 Position;
        float Rotation;
    };

    struct RigidbodyComponent
    {
        bool IsDynamic;
        bool FixedRotation;

        void* PhysicBody;
    };

    struct BoxColliderComponent
    {
        Vector2 Offset;
        Vector2 HalfExtents;

		float Density = 1.0f;
		float Friction = 0.5f;
		float Restitution = 0.0f;
		float RestitutionThreshold = 0.5f;

        void* PhysicFixture;
    };

    struct SpriteComponent
    {
        Texture2D Texture;
    };

    struct CircleComponent
    {
        float Radius;
    };

    struct TextComponent
    {
        std::string Text;
    };

    struct ScriptComponent
    {
        void (*UpdateFunction)(Entity, float);
    };
}