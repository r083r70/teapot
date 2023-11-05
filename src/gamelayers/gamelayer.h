#pragma once

namespace Teapot
{
    class Scene;

    class GameLayer
    {
    public:
        virtual void Load(Scene& scene) {}
        virtual void Start(Scene& scene) {}
        virtual void Update(Scene& scene, float deltaTime) {}
        virtual void Stop(Scene& scene) {}
    }; 
}
