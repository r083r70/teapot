#pragma once
#include <cassert>
#include <entt.hpp>
#include "scene.h"

namespace Teapot
{
    class Entity
    {
    public:
        Entity(Scene* scene, entt::entity handle);

        operator bool() const { return m_Handle != entt::null; }
        operator entt::entity() const { return m_Handle; }

        template<typename C, typename... Args>
        C& AddComponent(Args&&... args);

        template<typename C>
        C& GetComponent();

        template<typename C>
        bool HasComponent();

    private:
        entt::entity m_Handle;
        Scene* m_Scene;
    };

    template<typename C, typename... Args>
    C& Entity::AddComponent(Args&&... args)
    {
        assert(!HasComponent<C>());
        return m_Scene->GetRegistry().emplace<C>(m_Handle, std::forward<Args>(args)...);
    }

    template<typename C>
    C& Entity::GetComponent()
    {
        assert(HasComponent<C>());
        return m_Scene->GetRegistry().get<C>(m_Handle);
    }

    template<typename C>
    bool Entity::HasComponent()
    {
        return m_Scene->GetRegistry().any_of<C>(m_Handle);
    }
}
