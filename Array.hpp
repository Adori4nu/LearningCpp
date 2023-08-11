#pragma once
#define COMPILE_DEBUG_MODE 1
#if COMPILE_DEBUG_MODE > 0
#include <stdexcept>
#endif
template<typename T, size_t S>
class Array
{
public:
    constexpr size_t Size() const { return S; }

    T& operator[](size_t index)
    {
#if COMPILE_DEBUG_MODE > 0
        if (!(index < S)) { throw std::runtime_error("🦄"); }
#endif
        return m_Data[index];
    }
    const T& operator[](size_t index) const
    {
#if COMPILE_DEBUG_MODE > 0
        if (!(index < S)) { throw std::runtime_error("🦄"); }
#endif
        return m_Data[index];
    }

    T* Data() { return m_Data; }
    const T* Data() const { return m_Data; }
private:
    T m_Data[S];
};