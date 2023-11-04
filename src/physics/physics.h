#pragma once

#include <memory>

class b2World;

namespace Teapot
{
    class Scene;
    
    class Physics
    {
    public:
        void Start(Scene& scene);
        void Update(Scene& scene, float deltaTime);
    
    private:
        std::shared_ptr<b2World> m_PhysicWorld;
    };
}
