#include "scriptmanager.h"

#include <ecs/components.h>
#include <ecs/entity.h>
#include <ecs/scene.h>
#include <ecs/scriptable.h>

namespace Teapot
{
    void ScriptManager::Update(Scene& scene, float deltaTime)
    {
        auto scritps =  scene.GetRegistry().view<ScriptComponent>();
        scritps.each([&scene, deltaTime](auto entity, auto& scriptCmp)
        {
            if (scriptCmp.Instance == nullptr)
            {
                scriptCmp.CreationFunction(scriptCmp);
                scriptCmp.Instance->m_Entity = Entity{&scene, entity};
                scriptCmp.Instance->OnCreate();
            }

            scriptCmp.Instance->OnUpdate(deltaTime);
        });
    }

    void ScriptManager::OnEntityDestroyed(Entity e)
    {
        if (!e.HasComponent<ScriptComponent>())
            return;

        auto& scriptCmp = e.GetComponent<ScriptComponent>();
        scriptCmp.Instance->OnDestroy();
        scriptCmp.DestructionFunction(scriptCmp);
    }
}