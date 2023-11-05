#include "application.h"
#include <raylib.h>

#include <gamelayers/gamelayer.h>
#include <gamelayers/scriptmanager.h>
#include <gamelayers/physics.h>

namespace Teapot
{
    Application* Application::s_Instance = nullptr;

    Application::Application(const char* name, int32_t width, int32_t height)
    {
        s_Instance = this;
        InitWindow(width, height, name);

        // Add default Layers
        AddGameLayer<Physics>();
        AddGameLayer<ScriptManager>();
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
            
            ExecOnGameLayers([this, deltaTime](auto layer) { layer->Update(m_Scene, deltaTime); });

            m_Renderer.Draw(m_Scene);
        }

        StopScene();
    }

    void Application::StartScene()
    {
        m_Scene = {};

        ExecOnGameLayers([this](auto layer) { layer->Load(m_Scene); });
        ExecOnGameLayers([this](auto layer) { layer->Start(m_Scene); });
    }
    
    void Application::StopScene()
    {
        ExecOnGameLayers([this](auto layer) { layer->Stop(m_Scene); });
    }
}