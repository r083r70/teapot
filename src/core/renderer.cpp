#include "renderer.h"
#include <raylib.h>

#include <ecs/components.h>
#include <ecs/scene.h>

namespace Teapot
{
    void Renderer::Draw(const Scene &scene)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        auto textView =  scene.GetRegistry().view<TextComponent, TransformComponent>();
        textView.each([](auto& text, auto& transform)
        {
            DrawText(text.Text.c_str(), transform.Position.x, transform.Position.y, 20, GREEN);
        });
        
        auto spriteView =  scene.GetRegistry().view<SpriteComponent, TransformComponent>();
        spriteView.each([](auto& sprite, auto& transform)
        {
            DrawTextureEx(sprite.Texture, transform.Position, transform.Rotation, 1, WHITE);
        });

        EndDrawing();
    }
}