#include "scriptmanager.h"

#include <ecs/components.h>
#include <ecs/entity.h>
#include <ecs/scene.h>
#include <ecs/scriptable.h>

namespace Teapot
{
    void ScriptManager::Start(Scene &scene)
    {
        auto scritps = scene.GetRegistry().view<ScriptComponent>();
        scritps.each([&scene](auto entity, auto& scriptCmp)
        {
            scriptCmp.CreationFunction(scriptCmp);

            scriptCmp.Instance->m_Entity = Entity{&scene, entity};
            scriptCmp.Instance->OnStart();
        });
    }

    void ScriptManager::Stop(Scene &scene)
    {
        auto scritps = scene.GetRegistry().view<ScriptComponent>();
        scritps.each([](auto entity, auto& scriptCmp)
        {
            scriptCmp.Instance->OnStop();
            scriptCmp.DestructionFunction(scriptCmp);
        });
    }

    void ScriptManager::Update(Scene& scene, float deltaTime)
    {
        auto scritps =  scene.GetRegistry().view<ScriptComponent>();
        scritps.each([deltaTime](auto entity, auto& scriptCmp)
        {
            scriptCmp.Instance->OnUpdate(deltaTime);
        });
    }
}