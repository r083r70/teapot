#include "dispatcher.h"

#include <ecs/components.h>
#include <ecs/entity.h>
#include <ecs/scene.h>

namespace Teapot
{
    void Dispatcher::UpdateScripts(Scene& scene, float deltaTime)
    {
        auto view =  scene.GetRegistry().view<const ScriptComponent>();
        view.each([&scene, deltaTime](auto entity, auto& scriptCmp)
        {
            scriptCmp.UpdateFunction(Entity{&scene, entity}, deltaTime);
        });
    }
}