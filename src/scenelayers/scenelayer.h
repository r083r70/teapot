#pragma once
#include <ecs/entity.h>

namespace Teapot
{
    class Scene;
    class Entity;

    class SceneLayer
    {
    public:
        virtual void Load(Scene& scene) {}
        virtual void Start(Scene& scene) {}
        virtual void Update(Scene& scene, float deltaTime) {}
        virtual void Stop(Scene& scene) {}

        virtual void OnEntityDestroyed(Entity entity) {}
    };
}
