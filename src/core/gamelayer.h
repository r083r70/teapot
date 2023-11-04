#pragma once

namespace Teapot
{
    class GameLayer
    {
    public:
        virtual void PostLoad(Scene& scene) {}
        virtual void PostStart(Scene& scene) {}
        virtual void PreUpdate(Scene& scene, float deltaTime) {}
        virtual void PostUpdate(Scene& scene, float deltaTime) {}
        virtual void PreStop(Scene& scene) {}
    }; 
}
