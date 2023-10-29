#pragma once
#include <entt.hpp>

namespace Teapot
{
    class Entity;

    class Scene
    {
    public:
        Scene();

        entt::registry& GetRegistry() { return m_Registry; }
        const entt::registry& GetRegistry() const { return m_Registry; }

        Entity CreateEntity();

    private:
        entt::registry m_Registry;
    };
}