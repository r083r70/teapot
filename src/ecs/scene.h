#pragma once
#include <entt.hpp>
#include <raylib.h>
#include <string_view>

#include "physics/physics.h"
#include "scripts/scriptmanager.h"

namespace Teapot
{
    class Entity;
    class UUID;

    enum class SceneState
    {
        None,
        Loaded,
        Running
    };

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

        void Start();
        void Stop();

        void Update(float deltaTime);

        entt::registry& GetRegistry() { return m_Registry; }
        const entt::registry& GetRegistry() const { return m_Registry; }

        Camera& GetCamera() { return m_Camera; }
        const Camera& GetCamera() const { return m_Camera; }

        Entity CreateEntity();
        Entity CreateEntityWithUUID(UUID uuid);
        Entity CreateEntityWithName(std::string_view name);

    private:
        entt::registry m_Registry;

        ScriptManager m_ScriptManager;
        Physics m_Physics;


        Camera m_Camera;

        SceneState m_State;
    };
}