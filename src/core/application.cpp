#include "application.h"
#include <raylib.h>

#include "ecs/components.h"
#include "ecs/entity.h"

namespace Teapot
{
    void MoveDown(Entity entity, float deltaTime)
    {
        entity.GetComponent<TransformComponent>().Position.y -= deltaTime * 3.f;
    }

    Application::Application(const char* name, int32_t width, int32_t height)
    {
        InitWindow(width, height, name);
        
        const float renderWidth = GetRenderWidth();
        const float renderHeight = GetRenderHeight();
        
        {
            Entity e = m_Scene.CreateEntity();
            e.GetComponent<TransformComponent>().Position = Vector2{ renderWidth * 0.5f, renderHeight * 0.5f };
            e.AddComponent<TextComponent>().Text = "Congrats! You created your first ECS!";
        }

        {
            Entity e = m_Scene.CreateEntity();
            e.GetComponent<TransformComponent>().Position = Vector2{ renderWidth * 0.5f, renderHeight };
            e.AddComponent<SpriteComponent>().Texture = LoadTexture("resources/teapot.png");
            e.AddComponent<ScriptComponent>().UpdateFunction = &MoveDown;
        }

        {
            Entity e = m_Scene.CreateEntity();
            e.GetComponent<TransformComponent>().Position = Vector2{ renderWidth * 0.5f, renderHeight };
            e.AddComponent<CircleComponent>().Radius = 50;
            e.AddComponent<RigidbodyComponent>().IsDynamic = true;
            e.AddComponent<BoxColliderComponent>().HalfExtents = Vector2{1,1};
        }
    }

    Application::~Application()
    {
        CloseWindow();
    }

    void Application::Run()
    {
        m_Physics.Init(m_Scene);

        while (!WindowShouldClose())
        {
            const float deltaTime = GetFrameTime();

            m_Dispatcher.UpdateScripts(m_Scene, deltaTime);
            m_Physics.Update(m_Scene, deltaTime);
            m_Renderer.Draw(m_Scene);
        }
    }
}