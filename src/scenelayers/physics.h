#pragma once
#include <memory>
#include <ecs/entity.h>
#include "scenelayer.h"

class b2World;

namespace Teapot
{
    class Scene;
    
    class Physics : public SceneLayer
    {
    public:
        virtual void Start(Scene& scene) override;
        virtual void Update(Scene& scene, float deltaTime) override;
        virtual void Stop(Scene& scene) override;

        virtual void OnEntityDestroyed(Entity e) override;

    private:
        void CreatePhysicBody(Entity entity);
    
    private:
        std::shared_ptr<b2World> m_PhysicWorld;
    };
}
