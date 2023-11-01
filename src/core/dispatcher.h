#pragma once

namespace Teapot
{
    class Scene;

    class Dispatcher
    {
    public:
        void Init(Scene& scene);
        void UpdateScripts(Scene& scene, float deltaTime);
    };
}