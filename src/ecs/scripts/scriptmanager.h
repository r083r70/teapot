#pragma once

namespace Teapot
{
    class Scene;

    class ScriptManager
    {
    public:
        void Start(Scene& scene);
        void Stop(Scene& scene);

        void Update(Scene& scene, float deltaTime);
    };
}