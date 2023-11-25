#pragma once
#include <vector>
#include <memory>

#include <ecs/scene.h>

#include "event.h"
#include "renderer.h"

namespace Teapot
{
    class Application 
    {
    public:
        Application(const char* name, int32_t width, int32_t height);
        ~Application();

        void Run();

        void BindOnSceneCreated(Event<Scene&>::Listener listener)
        {
            m_OnSceneCreated.AddListener(listener);
        }

    protected:
        void StartScene();
        void StopScene();

    private:
        static Application* s_Instance;

        Scene m_Scene;
        Renderer m_Renderer;

        // Events
        Event<Scene&> m_OnSceneCreated;
    };
}