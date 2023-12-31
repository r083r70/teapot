#include <scenelayers/scenelayer.h>
#include "scene.h"
#include "entity.h"
#include "components.h"

namespace Teapot
{
    Scene::Scene()
    { }

    void Scene::Start()
    {
        ExecOnLayers([this](auto layer) { layer->Start(*this); });
        m_AliveTime = 0;
    }

    void Scene::Update(float deltaTime)
    {
        ExecOnLayers([this, deltaTime](auto layer) { layer->Update(*this, deltaTime); });
        m_AliveTime += deltaTime;
    }

    void Scene::Stop()
    {
        ExecOnLayers([this](auto layer) { layer->Stop(*this); });
    }

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

    void Scene::DestroyEntity(Entity entity)
    {
        ExecOnLayers([entity](auto layer) { layer->OnEntityDestroyed(entity); });
        m_Registry.destroy(entity);
    }

    template <class F>
    void Scene::ExecOnLayers(const F&& f)
    {
        for (auto it = m_Layers.begin(); it != m_Layers.end(); ++it)
        {
            f(*it);
        };
    }
}