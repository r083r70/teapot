#pragma once
#include "entity.h"

namespace Teapot
{
    class Scriptable
    {
    public:
        virtual ~Scriptable() {}

    protected:
        virtual void OnStart() {};
        virtual void OnUpdate(float deltaTime) {};
        virtual void OnStop() {};

    protected:
        Entity m_Entity;
        friend class Dispatcher;
    };
}