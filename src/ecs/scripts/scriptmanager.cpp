#include "scriptmanager.h"

#include "../components.h"
#include "../entity.h"
#include "../scene.h"
#include "scriptable.h"

namespace Teapot
{
    void ScriptManager::Start(Scene &scene)
    {
        auto scritps = scene.GetRegistry().view<ScriptComponent>();
        scritps.each([&scene](auto entity, auto& scriptCmp)
        {
            scriptCmp.InstantiateFunction(scriptCmp);

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
            scriptCmp.DestroyFunction(scriptCmp);
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