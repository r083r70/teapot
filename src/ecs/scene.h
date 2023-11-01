#pragma once
#include <entt.hpp>
#include <raylib.h>

namespace Teapot
{
    class Entity;

    struct Camera
    {
        Vector2 Position = Vector2(0,0);
        float Rotation = 0.f;
        float Zoom = 1.f;
    };

    class Scene
    {
    public:
        Scene();

        entt::registry& GetRegistry() { return m_Registry; }
        const entt::registry& GetRegistry() const { return m_Registry; }

        Camera& GetCamera() { return m_Camera; }
        const Camera& GetCamera() const { return m_Camera; }

        Entity CreateEntity();

    private:
        entt::registry m_Registry;
        Camera m_Camera;
    };
}