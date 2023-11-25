#pragma once
#include <entt.hpp>
#include <raylib.h>
#include <string_view>

namespace Teapot
{
    class Entity;
    class SceneLayer;
    class UUID;

    using SceneLayerPtr = std::shared_ptr<SceneLayer>;

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
        void Update(float deltaTime);
        void Stop();

        void AddLayer(SceneLayerPtr layer) { m_Layers.push_back(layer); }

        entt::registry& GetRegistry() { return m_Registry; }
        const entt::registry& GetRegistry() const { return m_Registry; }

        Camera& GetCamera() { return m_Camera; }
        const Camera& GetCamera() const { return m_Camera; }

        Entity CreateEntity();
        Entity CreateEntityWithUUID(UUID uuid);
        Entity CreateEntityWithName(std::string_view name);

        void DestroyEntity(Entity entity);

    private:
        template<class F>
        void ExecOnLayers(const F&&);

    private:
        std::vector<SceneLayerPtr> m_Layers;
        entt::registry m_Registry;
        Camera m_Camera;

        float m_AliveTime;
    };
}