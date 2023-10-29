#include "application.h"
#include <raylib.h>

#include "ecs/components.h"
#include "ecs/entity.h"

namespace Teapot
{
    Application::Application(const char* name, int32_t width, int32_t height)
    {
        InitWindow(width, height, name);

        Entity e = m_Scene.CreateEntity();
        e.AddComponent<TextComponent>().Text = "Congrats! You created your first ECS!";
    }

    Application::~Application()
    {
        CloseWindow();
    }

    void Application::Run()
    {
        while (true)
        {
            if (WindowShouldClose())
                break;

            m_Renderer.Draw(m_Scene);
        }
    }
}