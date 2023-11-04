#include "application.h"
#include <raylib.h>

#include "gamelayer.h"

namespace Teapot
{
    Application* Application::s_Instance = nullptr;

    Application::Application(const char* name, int32_t width, int32_t height)
    {
        s_Instance = this;
        InitWindow(width, height, name);
    }

    Application::~Application()
    {
        CloseWindow();
    }

    void Application::Run()
    {
        StartScene();

        while (!WindowShouldClose())
        {
            const float deltaTime = GetFrameTime();
            
            ExecOnGameLayers([this, deltaTime](auto layer) { layer->PreUpdate(m_Scene, deltaTime); });
            m_Scene.Update(deltaTime);
            ExecOnGameLayers([this, deltaTime](auto layer) { layer->PostUpdate(m_Scene, deltaTime); });

            m_Renderer.Draw(m_Scene);
        }

        StopScene();
    }

    void Application::StartScene()
    {
        m_Scene = {};
        ExecOnGameLayers([this](auto layer) { layer->PostLoad(m_Scene); });

        m_Scene.Start();
        ExecOnGameLayers([this](auto layer) { layer->PostStart(m_Scene); });
    }
    
    void Application::StopScene()
    {
        ExecOnGameLayers([this](auto layer) { layer->PreStop(m_Scene); });
        m_Scene.Start();
    }
}