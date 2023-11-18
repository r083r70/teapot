#pragma once
#include "scenelayer.h"

namespace Teapot
{
    class Scene;

    class ScriptManager : public SceneLayer
    {
    public:
        virtual void Update(Scene& scene, float deltaTime) override;
        virtual void OnEntityDestroyed(Entity e) override;
    };
}