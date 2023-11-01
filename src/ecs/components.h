#pragma once
#include <string>
#include <raylib.h>

#include "scripts.h"

namespace Teapot
{
    class Entity;

    enum class RigidbodyType { Static, Dynamic, Kinematic };
    
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
        Vector2 Position = Vector2(0,0);
        float Rotation = 0.f;
        float Scale = 1.f;
    };

    struct RigidbodyComponent
    {
        RigidbodyType Type = RigidbodyType::Static;
        bool FixedRotation = true;

        void* PhysicBody = nullptr;
    };

    struct BoxColliderComponent
    {
        Vector2 Offset = Vector2(0,0);
        Vector2 HalfExtents = Vector2(.5f,.5f);

		float Density = 1.0f;
		float Friction = 0.5f;
		float Restitution = 0.0f;
		float RestitutionThreshold = 0.5f;

        void* PhysicFixture = nullptr;
    };

    struct SpriteComponent
    {
        Texture2D Texture;
        Color Tint = WHITE;
    };

    struct CircleComponent
    {
        float Radius = 1.f;
        Color Tint = WHITE;
    };

    struct TextComponent
    {
        std::string Text;

        Font TextFont = GetFontDefault();
        int32_t FontSize = 10;
        int32_t Spacing = 1;

        Color Tint = BLACK;
    };

    struct ScriptComponent
    {
        Scriptable* Instance;
        Scriptable* (*InstantiateFunction)();

        ~ScriptComponent()
        {
            delete Instance;
        }

        template<class T>
        void Bind()
        {
            InstantiateFunction = []() { return static_cast<Scriptable*>(new T()); };
        }
    };
}