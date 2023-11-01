#include "renderer.h"
#include <raylib.h>
#include <raymath.h>

#include <ecs/components.h>
#include <ecs/scene.h>

namespace Teapot
{
    void Renderer::Draw(const Scene& scene)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Camera
        {
            const Camera& camera = scene.GetCamera();
            Camera2D camera2d;
            camera2d.target = camera.Position;
            camera2d.offset = Vector2{ GetRenderWidth()*0.5f, GetRenderHeight()*0.5f };
            camera2d.rotation = camera.Rotation;
            camera2d.zoom = camera.Zoom;

            BeginMode2D(camera2d);

            auto sprites = scene.GetRegistry().view<const SpriteComponent, const TransformComponent>();
            sprites.each([](auto &spriteCmp, auto &transformCmp)
            {
                const float halfWidth = spriteCmp.Texture.width * 0.5f;
                const float halfHeight = spriteCmp.Texture.height * 0.5f;
                Vector2 drawPosition = Vector2Multiply(transformCmp.Position, { 1.f, -1.f });
                drawPosition = Vector2Subtract(drawPosition, { halfWidth, halfHeight });

                DrawTextureEx(spriteCmp.Texture, drawPosition, transformCmp.Rotation, transformCmp.Scale, spriteCmp.Tint);
            });

            auto cicles = scene.GetRegistry().view<const CircleComponent, const TransformComponent>();
            cicles.each([](auto &circleCmp, auto &transformCmp)
            {
                const Vector2 drawPosition = Vector2Multiply(transformCmp.Position, { 1.f, -1.f });
                const float scaledRadius = circleCmp.Radius * transformCmp.Scale;

                DrawCircleLinesV(drawPosition, scaledRadius, circleCmp.Tint);
            });
            
            EndMode2D();
        }

        // UI
        {
            auto texts = scene.GetRegistry().view<const TextComponent, const TransformComponent>();
            texts.each([](auto &textCmp, auto &transformCmp)
            {
                const int32_t scaledFontSize = textCmp.FontSize * transformCmp.Scale;

                const Vector2 extents = MeasureTextEx(textCmp.TextFont, textCmp.Text.c_str(), scaledFontSize, textCmp.Spacing);
                const Vector2 halfExtents = Vector2Scale(extents, 0.5f);
                const Vector2 drawPosition = Vector2Subtract(transformCmp.Position, halfExtents);

                DrawTextEx(textCmp.TextFont, textCmp.Text.c_str(), drawPosition, scaledFontSize, textCmp.Spacing, textCmp.Tint);
            });
        }

        EndDrawing();
    }
}