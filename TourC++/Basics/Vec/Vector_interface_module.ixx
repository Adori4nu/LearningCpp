module;

#include <iostream>
#include <stdexcept>
#include <string>

export module Vector;
#ifndef VEC_IMP
    #define VEC_IMP 52
#endif
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
#if VEC_IMP == 40
#pragma region 4_0_Vec

export template<typename T>
class Vector{

    T* elem;
    size_t sz;

public:
    Vector(size_t size);
    T& operator[](size_t i);
    size_t size() { return sz; }
};

export template<typename T>
Vector<T>::Vector(size_t size)
{
    if (size < 0)
        throw std::length_error{"konstruktor klasy Vector: ujemny rozmiar.\n"};
}

export template<typename T>
T& Vector<T>::operator[](size_t i)
{
    if (i < 0 || size() <= i)
        throw std::out_of_range{"Vector::operator[]\n"};
    return elem[i];
}

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
#if VEC_IMP == 45
#pragma region 4_5_Vec

enum class Error_action { ignore, throwing, terminating, logging };
// throwing is crashing even with try catch in read and sum for msvc, g++ is fine
constexpr Error_action default_Error_action = Error_action::logging;

enum class Error_code { range_error, length_error };

std::string error_code_name[] { "range error", "length error" };

template<Error_action action = default_Error_action, class C>
constexpr void expect(C cond, Error_code x)
{
    if constexpr (action == Error_action::logging)
        if (!cond()) std::cerr << "expect() failure: " << int(x) << ' '
         << error_code_name[int(x)] << '\n';
    if constexpr (action == Error_action::throwing)
        if (!cond()) throw x;
    if constexpr (action == Error_action::terminating)
        if (!cond()) terminate();
}

export template<typename T>
class Vector{

    T* elem;
    size_t sz;

public:
    Vector(size_t size);
    T& operator[](size_t i);
    size_t size() { return sz; }
};

export template<typename T>
Vector<T>::Vector(size_t size)
{
    if (size < 0)
        throw std::length_error{"konstruktor klasy Vector: ujemny rozmiar.\n"};
}

export template<typename T>
T& Vector<T>::operator[](size_t i)
{
    expect([i, this] { return 0 <= i && i < size(); }, Error_code::range_error);
    return elem[i];
}

export template<typename T>
void read_and_sum(T& result, size_t s)
{
    Vector<T> v(s);
    for (size_t i{0}; i != s; ++i)
    {   // try catch needed for msvc to work
        try
        {
            std::cin >> v[i];
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    
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
#if VEC_IMP == 52
#pragma region 5_2_Vec

enum class Error_action { ignore, throwing, terminating, logging };
// throwing is crashing even with try catch in read and sum for msvc, g++ is fine
constexpr Error_action default_Error_action = Error_action::logging;

enum class Error_code { range_error, length_error };

std::string error_code_name[] { "range error", "length error" };

template<Error_action action = default_Error_action, class C>
constexpr void expect(C cond, Error_code x)
{
    if constexpr (action == Error_action::logging)
        if (!cond()) std::cerr << "expect() failure: " << int(x) << ' '
         << error_code_name[int(x)] << '\n';
    if constexpr (action == Error_action::throwing)
        if (!cond()) throw x;
    if constexpr (action == Error_action::terminating)
        if (!cond()) terminate();
}

export template<typename T>
class Vector{

    T* elem;
    size_t sz;

public:
    Vector(size_t size) : elem{new T[size]}, sz{size}
    Vecotr(std::initializer_list<T>);
    ~Vector() { delete[] elem; }
    T& operator[](size_t i);
    size_t size() { return sz; }
    void push_back(T);
};

export template<typename T>
Vector<T>::Vector(size_t size) : elem{new T[size]}, sz{size}
{
    // if (size < 0)
    //     throw std::length_error{"konstruktor klasy Vector: ujemny rozmiar.\n"};

    for (size_t i{ 0 }; i != s; ++i)
    {
        elem[i] = T();
    }
}

export template<typename T>
Vector<T>::Vector(std::initializer_list<T>)
{

}

export template<typename T>
T& Vector<T>::operator[](size_t i)
{
    expect([i, this] { return 0 <= i && i < size(); }, Error_code::range_error);
    return elem[i];
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

export template<typename T>
void Vector<T>::push_back(T value)
{

}

export template<typename T>
void read_and_sum(T& result, size_t s)
{
    Vector<T> v(s);
    for (size_t i{0}; i != s; ++i)
    {   // try catch needed for msvc to work
        try
        {
            std::cin >> v[i];
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    
    result = {};
    for (size_t i{0}; i != s; ++i)
        result += v[i];
}

export template<typename T>
Vector<T> read(std::istream& is)
{
    Vector<T> vec;
}
#pragma endregion
#endif
