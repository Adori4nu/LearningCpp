#pragma once
#define COMPILE_DEBUG_MODE 1
#if COMPILE_DEBUG_MODE > 0
#include <stdexcept>
#include <cassert>
#endif
// #include <memory> // C++20

template<class Vector>
class VectorIterator
{
public:
    using ValueType = typename Vector::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;

public:
    VectorIterator(PointerType ptr) : m_Ptr(ptr) {};

    VectorIterator& operator++()
    {
        m_Ptr++;
        return *this;
    }

    VectorIterator operator++(int)
    {
        VectorIterator iterator = *this;
        ++(*this);
        return iterator;
    }

    VectorIterator& operator--()
    {
        m_Ptr--;
        return *this;
    }

    VectorIterator operator--(int)
    {
        VectorIterator iterator = *this;
        --(*this);
        return iterator;
    }

    std::ptrdiff_t operator-(const VectorIterator& other) const {
        return m_Ptr - other.m_Ptr;
    }

    VectorIterator operator+(int n) const {
        return VectorIterator(m_Ptr + n);
    }

    ReferenceType operator[](int index)
    {
        return *(m_Ptr + index);
    }

    PointerType operator->()
    {
        return m_Ptr;
    }

    ReferenceType operator*()
    {
        return *m_Ptr;
    }

    bool operator==(const VectorIterator& other) const
    {
        return m_Ptr == other.m_Ptr;
    }

    bool operator!=(const VectorIterator& other) const
    {
        return !(*this == other);
    }

private:
    PointerType m_Ptr;

};

template<typename T>
class Vector
{
public:
    using ValueType = T;
    using Iterator = VectorIterator<Vector<T>>;
private:
    T* m_Data = nullptr;
    
    size_t m_Size = 0;
    size_t m_Capacity = 0;

    void ReAlloc(size_t new_Capacity);
public:
    Vector()
    {
        ReAlloc(2);
    }

    ~Vector()
    {
        Clear();
        // delete[] m_Data;
        ::operator delete(m_Data, m_Capacity * sizeof(T));
    }

    void PushBack(const T& value);
    void PushBack(T&& value);

    template<typename... Args>
    T& EmplaceBack(Args&&... args);

    void PopBack();

    void Clear();

    inline const size_t Size() const { return m_Size; };

    
    VectorIterator<Vector<T>> begin();
    VectorIterator<Vector<T>> end();

    const T& operator[](size_t index) const;
    T& operator[](size_t index) { return m_Data[index]; };

    const T& front() const { 
    #if COMPILE_DEBUG_MODE > 0
        assert(m_Size > 0 && "Cannot call front() on empty vector");
    #endif
        return *begin();
    }
    T& front() {  // or
    #if COMPILE_DEBUG_MODE > 0
        assert(m_Size > 0 && "Cannot call front() on empty vector");
    #endif
        return m_Data[0]; 
    }
    const T& back() const { 
    #if COMPILE_DEBUG_MODE > 0
        assert(m_Size > 0 && "Cannot call front() on empty vector");
    #endif
        return *(end() - 1);
    }
    T& back() {  // or
    #if COMPILE_DEBUG_MODE > 0
        assert(m_Size > 0 && "Cannot call front() on empty vector");
    #endif
        return m_Data[m_Size - 1]; 
    }
};

template<typename T>
void Vector<T>::ReAlloc(size_t new_Capacity)
{
    T* n_Block = (T*)::operator new(new_Capacity * sizeof(T));
    // T* n_Block = ::operator new T[new_Capacity];

    if (new_Capacity < m_Size)
        m_Size = new_Capacity;

    for (size_t i = 0; i < m_Size; i++)
        // n_Block[i] = std::move(m_Data[i]); // Move On unitialized memory which is not type T yet
        new(&n_Block[i]) T(std::move(m_Data[i]));

    for (size_t i = 0; i < m_Size; i++)
        m_Data[i].~T();

    ::operator delete(m_Data, m_Capacity * sizeof(T));
    // delete[] m_Data;
    m_Data = n_Block;
    m_Capacity = new_Capacity;
}

template<typename T>
void Vector<T>::PushBack(const T& value)
{
    if (m_Size >= m_Capacity)
    {
        ReAlloc(m_Capacity + m_Capacity / 2);
    }

    new(m_Data + m_Size) T(value);
    m_Size++;
}

template<typename T>
void Vector<T>::PushBack(T&& value)
{
    if (m_Size >= m_Capacity)
    {
        ReAlloc(m_Capacity + m_Capacity / 2);
    }

    new(m_Data + m_Size) T(std::move(value));
    m_Size++;
}

template<typename T>
template<typename... Args>
T& Vector<T>::EmplaceBack(Args&&... args)
{
    if (m_Size >= m_Capacity)
        ReAlloc(m_Capacity + m_Capacity / 2);

    // new()
    // std::construct_at(&m_Data[m_Size], T(std::forward<Args>(args)...)); // C++20
    // new(&m_Data[m_Size]) T(std::forward<Args>(args)...); // << no need for that we can add size_t to m_Data which is a pointer to move length of x values on our memory block
    new(m_Data + m_Size) T(std::forward<Args>(args)...); // placment new creates object directly at memory m_Data[m_Size] no moving and destroing
    // m_Data[m_Size] = T(std::forward<Args>(args)...); // it is still moveing and destroing temporary
    return m_Data[m_Size++];
}

template<typename T>
void Vector<T>::PopBack()
{
    if (m_Size > 0)
    {
        m_Size--;
        m_Data[m_Size].~T();
    }
}

template<typename T>
void Vector<T>::Clear()
{
    for (size_t i = 0; i < m_Size; i++)
        m_Data[i].~T();
    
    m_Size = 0;
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const
{
#if COMPILE_DEBUG_MODE > 0
    if (index >= m_Size)
    {
        // static_assert
    }
#endif
    return m_Data[index];
}

template<class T>
VectorIterator<Vector<T>> Vector<T>::begin()
{
    return Iterator(m_Data);
}

template<class T>
VectorIterator<Vector<T>> Vector<T>::end()
{
    return Iterator(m_Data + m_Size);
}