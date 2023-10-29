#include "renderer.h"
#include <raylib.h>

#include <ecs/components.h>
#include <ecs/scene.h>

namespace Teapot
{
    void Renderer::Draw(const Scene& scene)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Sprites
        {
            auto view = scene.GetRegistry().view<const SpriteComponent, const TransformComponent>();
            view.each([](auto &spriteCmp, auto &transformCmp)
            {
                const float halfWidth = spriteCmp.Texture.width * 0.5f;
                const float halfHeight = spriteCmp.Texture.height * 0.5f;
                const Vector2 drawPosition =
                {
                    transformCmp.Position.x - halfWidth,
                    GetRenderHeight() - transformCmp.Position.y - halfHeight
                };
                
                DrawTextureEx(spriteCmp.Texture, drawPosition, transformCmp.Rotation, 1, WHITE);
            });
        }

        // Circles
        {
            auto view = scene.GetRegistry().view<const CircleComponent, const TransformComponent>();
            view.each([](auto &circleCmp, auto &transformCmp)
            {
                const Vector2 drawPosition = { transformCmp.Position.x, GetRenderHeight() - transformCmp.Position.y };
                DrawCircleLinesV(drawPosition, circleCmp.Radius, RED);
            });
        }

        // Texts
        {
            auto view = scene.GetRegistry().view<const TextComponent, const TransformComponent>();
            view.each([](auto &textCmp, auto &transformCmp)
            {
                const float halfWidth = MeasureText(textCmp.Text.c_str(), 20) * 0.5f;
                const float halfHeight = 10;
                const Vector2 drawPosition =
                {
                    transformCmp.Position.x - halfWidth,
                    GetRenderHeight() - transformCmp.Position.y - halfHeight
                };

                DrawText(textCmp.Text.c_str(), drawPosition.x, drawPosition.y, 20, GREEN);
            });
        }

        EndDrawing();
    }
}