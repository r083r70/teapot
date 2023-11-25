#pragma once
#include <functional>
#include <vector>

// BaseEvent
// HandledEvent

template<typename... Args>
class Event
{
public:
    using Listener = std::function<void(Args...)>;

    void AddListener(Listener f) { m_Listeners.push_back(f); }
    void Broadcast(Args... args)
    {
        for (auto it = m_Listeners.begin(); it != m_Listeners.end(); ++it)
            (*it)(args...);
    }

private:
    std::vector<Listener> m_Listeners;
};