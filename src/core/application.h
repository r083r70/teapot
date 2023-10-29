#pragma once
#include <vector>
#include <memory>

#include <ecs/scene.h>

#include "renderer.h"

namespace Teapot
{
    class Application 
    {
    public:
        Application(const char* name, int32_t width, int32_t height);
        ~Application();

        void Run();

    private:
        Renderer m_Renderer;
        Scene m_Scene;
    };
}