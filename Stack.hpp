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
    Node(const Type& value) : m_prev(this) m_value(value) {};
private:
    Node* m_prev;
    Type m_value;
};

template <typename Type>
class Stack
{
public:
    Stack() : m_size(0) {};
    ~Stack();

    void push();
    Type& pop();
    Type& peek();

    inline bool isEmpty() const { return m_size == 0; };
    inline size_t getSize() const { return m_size; };

private:
    size_t m_size;
    Node<Type> m_top;
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
    if
}