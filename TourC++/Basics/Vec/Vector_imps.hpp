#pragma once
// #define VEC_IMP 23

#if VEC_IMP == 22
#pragma region 2_2_Vec

#include <iostream>

template<typename T>
struct Vector{
    T* elem;
    size_t sz;
};

template<typename T>
void vector_init(Vector<T>& v, size_t s)
{
    v.elem = new T[s];
    v.sz = s;
}

template<typename T>
void read_and_sum(T& result, size_t s)
{
    Vector<T> v;
    vector_init(v, s);
    for (size_t i{0}; i != s; ++i)
        std::cin >> v.elem[i];
    
    result = {};
    for (size_t i{0}; i != s; ++i)
        result += v.elem[i];
}
#pragma endregion
#endif

#if VEC_IMP == 23
#pragma region 2_3_Vec
#include <iostream>
// export module Vector;

template<typename T>
/*export*/ class Vector{

    T* elem;
    size_t sz;

public:
    Vector(size_t size) : elem{new T[size]}, sz{size} {}
    T& operator[](size_t i) { return elem[i]; }
    size_t size() { return sz; }
};

// export
template<typename T>
void read_and_sum(T& result, size_t s)
{
    Vector<T> v(s);
    for (size_t i{0}; i != s; ++i)
        std::cin >> v[i];
    
    result = {};
    for (size_t i{0}; i != s; ++i)
        result += v[i];
}
#pragma endregion
#endif