#include "scene.h"
#include "entity.h"
#include "components.h"

namespace Teapot
{
    Scene::Scene()
    {
    }

    Entity Scene::CreateEntity()
    {
        static int64_t GlobalID = 0;

        entt::entity entityHandle = m_Registry.create();
        m_Registry.emplace<UUIDComponent>(entityHandle, GlobalID++);
        m_Registry.emplace<NameComponent>(entityHandle);
        m_Registry.emplace<TransformComponent>(entityHandle);

        return Entity(this, entityHandle);
    }
}