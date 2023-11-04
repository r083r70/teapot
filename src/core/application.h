#pragma once
#include <vector>
#include <memory>

#include <ecs/scene.h>

#include "renderer.h"

namespace Teapot
{
    class GameLayer;

    class Application 
    {
    public:
        Application(const char* name, int32_t width, int32_t height);
        ~Application();

        template<class T>
        void AddGameLayer();
        
        void Run();

    protected:
        void StartScene();
        void StopScene();

        template<class F>
        void ExecOnGameLayers(const F&&);

    private:
        static Application* s_Instance;

        Scene m_Scene;
        Renderer m_Renderer;
        std::vector<std::shared_ptr<GameLayer>> m_Layers;
    };

    template <class T>
    void Application::AddGameLayer()
    {
        m_Layers.push_back(std::make_shared<T>());
    }

    template <class F>
    void Application::ExecOnGameLayers(const F&& f)
    {
        std::for_each(m_Layers.begin(), m_Layers.end(), [f](auto layer)
        {
            f(layer);
        });
    }
}