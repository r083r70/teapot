#include "entity.h"

namespace Teapot
{
    Entity::Entity(Scene* scene, entt::entity handle)
        : m_Handle(handle)
        , m_Scene(scene)
    {}
}