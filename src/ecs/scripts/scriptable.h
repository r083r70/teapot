#pragma once
#include "../entity.h"

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

        template<typename T>
        T& GetComponent();

    private:
        Entity m_Entity;
        friend class ScriptManager;
    };

    template<typename T>
    T& Scriptable::GetComponent()
    {
        return m_Entity.GetComponent<T>();
    }
}