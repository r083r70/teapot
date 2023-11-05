#include "core/application.h"

#include <ecs/components.h>
#include <ecs/scene.h>
#include <gamelayers/gamelayer.h>

class MoveDown : public Teapot::Scriptable
{
    virtual void OnUpdate(float deltaTime) override
    {
        GetComponent<Teapot::TransformComponent>().Position.y -= deltaTime * 3.f;
    }
};

class SimpleGameLayer : public Teapot::GameLayer
{
public:
    virtual void Load(Teapot::Scene& scene) override
    {
        {
            const float renderWidth = GetRenderWidth();
            const float renderHeight = GetRenderHeight();

            Teapot::Entity e = scene.CreateEntity();
            e.GetComponent<Teapot::TransformComponent>().Position;
            e.AddComponent<Teapot::TextComponent>().Text = "Congrats! You created your first ECS!";
        }

        {
            Teapot::Entity e = scene.CreateEntity();
            e.GetComponent<Teapot::TransformComponent>().Position.y = 200;
            e.AddComponent<Teapot::SpriteComponent>().Texture = LoadTexture("resources/teapot.png");
            e.AddComponent<Teapot::ScriptComponent>().Bind<MoveDown>();
        }

        {
            Teapot::Entity e = scene.CreateEntity();
            e.GetComponent<Teapot::TransformComponent>().Position.y = 200;
            e.AddComponent<Teapot::CircleComponent>().Radius = 50;
            e.AddComponent<Teapot::RigidbodyComponent>().Type = Teapot::RigidbodyType::Dynamic;
            e.AddComponent<Teapot::BoxColliderComponent>().HalfExtents = Vector2{1,1};
        }
    }
};

int main(void)
{
    Teapot::Application app("Test", 800, 400);
    app.AddGameLayer<SimpleGameLayer>();
    app.Run();
    
    return 0;
}