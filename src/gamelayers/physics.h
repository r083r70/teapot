#pragma once
#include <memory>
#include "gamelayer.h"

class b2World;

namespace Teapot
{
    class Scene;
    
    class Physics : public GameLayer
    {
    public:
        virtual void Start(Scene& scene) override;
        virtual void Update(Scene& scene, float deltaTime) override;
    
    private:
        std::shared_ptr<b2World> m_PhysicWorld;
    };
}
