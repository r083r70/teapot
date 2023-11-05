#include "scene.h"
#include "entity.h"
#include "components.h"

namespace Teapot
{
    Scene::Scene()
    { }

    Entity Scene::CreateEntity()
    {
        entt::entity entityHandle = m_Registry.create();
        m_Registry.emplace<IDComponent>(entityHandle);
        m_Registry.emplace<NameComponent>(entityHandle);
        m_Registry.emplace<TransformComponent>(entityHandle);

        return Entity(this, entityHandle);
    }
    
    Entity Scene::CreateEntityWithUUID(UUID uuid)
    {
        Entity e = CreateEntity();
        e.GetComponent<IDComponent>().ID = uuid;
        return e;
    }

    Entity Scene::CreateEntityWithName(std::string_view name)
    {
        Entity e = CreateEntity();
        e.GetComponent<NameComponent>().Name = name;
        return e;
    }
}