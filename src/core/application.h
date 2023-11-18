#pragma once
#include <vector>
#include <memory>

#include <ecs/scene.h>

#include "renderer.h"

namespace Teapot
{
    class SceneLayer;
    using SceneLayerBuilder = std::function<std::shared_ptr<SceneLayer>()>;

    class Application 
    {
    public:
        Application(const char* name, int32_t width, int32_t height);
        ~Application();

        void AddSceneLayerBuilders(SceneLayerBuilder builder);

        void Run();

    protected:
        void StartScene();
        void StopScene();

    private:
        static Application* s_Instance;

        Scene m_Scene;
        Renderer m_Renderer;

        std::vector<SceneLayerBuilder> m_SceneLayerBuilders;
    };

}