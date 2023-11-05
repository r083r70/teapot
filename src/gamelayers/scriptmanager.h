#pragma once
#include "gamelayer.h"

namespace Teapot
{
    class Scene;

    class ScriptManager : public GameLayer
    {
    public:
        virtual void Start(Scene& scene) override;
        virtual void Update(Scene& scene, float deltaTime) override;
        virtual void Stop(Scene& scene) override;
    };
}