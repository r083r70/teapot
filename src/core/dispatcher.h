#pragma once

namespace Teapot
{
    class Scene;

    class Dispatcher
    {
    public:
        void UpdateScripts(Scene& scene, float deltaTime);
    };
}