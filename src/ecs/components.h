#pragma once
#include <string>
#include <raylib.h>

namespace Teapot
{
    struct UUIDComponent
    {
        int64_t UUID;
    };

    struct NameComponent
    {
        std::string Name;
    };

    struct TransformComponent
    {
        Vector2 Position;
        float Rotation;
    };

    struct SpriteComponent
    {
        Texture2D Texture;
    };

    struct TextComponent
    {
        std::string Text;
    };
}