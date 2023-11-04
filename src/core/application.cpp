#include "application.h"
#include <raylib.h>

#include "ecs/components.h"
#include "ecs/entity.h"

namespace Teapot
{
    class MoveDown : public Scriptable
    {
        virtual void OnUpdate(float deltaTime) override
        {
            GetComponent<TransformComponent>().Position.y -= deltaTime * 3.f;
        }
    };

    Application::Application(const char* name, int32_t width, int32_t height)
    {
        InitWindow(width, height, name);
        
        {
            const float renderWidth = GetRenderWidth();
            const float renderHeight = GetRenderHeight();

            Entity e = m_Scene.CreateEntity();
            e.GetComponent<TransformComponent>().Position;
            e.AddComponent<TextComponent>().Text = "Congrats! You created your first ECS!";
        }

        {
            Entity e = m_Scene.CreateEntity();
            e.GetComponent<TransformComponent>().Position.y = 200;
            e.AddComponent<SpriteComponent>().Texture = LoadTexture("resources/teapot.png");
            e.AddComponent<ScriptComponent>().Bind<MoveDown>();
        }

        {
            Entity e = m_Scene.CreateEntity();
            e.GetComponent<TransformComponent>().Position.y = 200;
            e.AddComponent<CircleComponent>().Radius = 50;
            e.AddComponent<RigidbodyComponent>().Type = RigidbodyType::Dynamic;
            e.AddComponent<BoxColliderComponent>().HalfExtents = Vector2{1,1};
        }
    }

    Application::~Application()
    {
        CloseWindow();
    }

    void Application::Run()
    {
        m_Scene.Start();

        while (!WindowShouldClose())
        {
            const float deltaTime = GetFrameTime();
            
            m_Scene.Update(deltaTime);
            m_Renderer.Draw(m_Scene);
        }

        m_Scene.Stop();
    }
}