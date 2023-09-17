#pragma once
#define COMPILE_DEBUG_MODE 1
#if COMPILE_DEBUG_MODE > 0
#include <stdexcept>
#endif

#include <stack>

template <typename Type>
class Node
{
public:
    Node() : m_prev(this) {};
    Node(const Type& value) : m_prev(this), m_value(value) {};
    Node* m_prev;
    Type m_value;
private:
};

template <typename Type>
class Stack
{
public:
    Stack() : m_size(0) { m_top = m_end = nullptr; };
    Stack(const Type& value) : m_size(0), m_top(value) {};
    ~Stack();

    void push();
    Type& pop();
    Type& peek();

    inline bool isEmpty() const { return m_size == 0; };
    inline size_t getSize() const { return m_size; };
protected:
    Node<Type> m_top{};
private:
    size_t m_size;
    Node<Type> m_end{};
};

template <typename Type>
void Stack<Type>::push()
{

}

template <typename Type>
Type& Stack<Type>::pop()
{
    
}

template <typename Type>
Type& Stack<Type>::peek()
{
    if (m_size) return m_top.m_value;
}