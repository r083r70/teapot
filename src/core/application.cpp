#include "application.h"
#include <raylib.h>

#include <scenelayers/scenelayer.h>
#include <scenelayers/scriptmanager.h>
#include <scenelayers/physics.h>

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
            m_Scene.Update(deltaTime);
            m_Renderer.Draw(m_Scene);
        }

        StopScene();
    }

    void Application::StartScene()
    {
        m_Scene = {};
        m_Scene.AddLayer(std::make_shared<Physics>());
        m_Scene.AddLayer(std::make_shared<ScriptManager>());
        
        m_OnSceneCreated.Broadcast(m_Scene);

        m_Scene.Start();
    }
    
    void Application::StopScene()
    {
        m_Scene.Stop();
    }
}