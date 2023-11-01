#pragma once
#include <cstdint>

namespace Teapot
{
    class UUID
    {
    public:
        UUID();
        UUID(const UUID&) = default;
        UUID(uint64_t value) : m_Value(value) {}

        uint64_t Get() const { return m_Value; }
        
        bool operator==(const UUID& other) { return m_Value == other.m_Value; }
        bool operator()() { return m_Value != 0;  }

    private:
        uint64_t m_Value = 0;
    };
}

namespace std
{
    template <typename T> struct hash;
    
    template<>
    struct hash<Teapot::UUID>
    {
        size_t operator()(const Teapot::UUID& uuid) const noexcept
        {
            return uuid.Get();
        }
    };
}
 