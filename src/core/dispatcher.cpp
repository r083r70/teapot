#include "dispatcher.h"

#include <ecs/components.h>
#include <ecs/entity.h>
#include <ecs/scene.h>

namespace Teapot
{
    void Dispatcher::Init(Scene &scene)
    {
        auto view =  scene.GetRegistry().view<ScriptComponent>();
        view.each([&scene](auto entity, auto& scriptCmp)
        {
            scriptCmp.Instance = scriptCmp.InstantiateFunction();
            scriptCmp.Instance->m_Entity = Entity{&scene, entity};
            scriptCmp.Instance->OnStart();
        });
    }

    void Dispatcher::UpdateScripts(Scene& scene, float deltaTime)
    {
        auto view =  scene.GetRegistry().view<ScriptComponent>();
        view.each([deltaTime](auto entity, auto& scriptCmp)
        {
            scriptCmp.Instance->OnUpdate(deltaTime);
        });
    }
}