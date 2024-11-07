module;

#include <iostream>

export module Vector;
#define VEC_IMP 30
#if VEC_IMP == 30
#pragma region 3_0_Vec

export template<typename T>
class Vector{

    T* elem;
    size_t sz;

public:
    Vector(size_t size) : elem{new T[size]}, sz{size} {}
    T& operator[](size_t i) { return elem[i]; }
    size_t size() { return sz; }
};

export template<typename T>
void read_and_sum(T& result, size_t s)
{
    Vector<T> v(s);
    for (size_t i{0}; i != s; ++i)
        std::cin >> v[i];
    
    result = {};
    for (size_t i{0}; i != s; ++i)
        result += v[i];
}

export template<typename T>
bool operator==(const Vector<T>& v1, const Vector<T>& v2)
{
    if (v1.size() != v2.size())
        return false;
    for (size_t i{0}; i < v1.size(); ++i)
        if (v1[i] != v2[i])
            return false;
    return true;
}
#pragma endregion
#endif