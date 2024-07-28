#pragma once
#define COMPILE_DEBUG_MODE 1
#if COMPILE_DEBUG_MODE > 0
#include <stdexcept>
#endif

#include <mutex>
#include <stack>

template <typename Type>
class Node
{
public:
    Node() : m_prev(this) {};
    Node(const Type& value) : m_prev(this), m_value(value) {};
    Node(const Type& value, Node* prev) : m_prev(prev), m_value(value) {};
    Node* m_prev;
    Type m_value;
private:
};

template <typename Type>
class Stack
{
public:
    Stack() : m_size(0), m_top(Type(), &m_end), m_end(Type(), nullptr) {};
    Stack(const Type& value) : m_size(1), m_top(value) {};
    ~Stack() {
        Node<Type>* current = m_top.m_prev;
        while (current != &m_end)
        {
            Node<Type>* tmp = current;
            current = current->m_prev;
            --m_size;
            delete tmp;
        }
    };

    void push(const Type& value);
    Type pop();
    Type peek();

    inline bool isEmpty() const { return m_size == 0; };
    inline size_t size() const { return m_size; };
protected:
    Node<Type> m_top{};
private:
    size_t m_size;
    Node<Type> m_end{};
    std::mutex mut;
};

template <typename Type>
void Stack<Type>::push(const Type& value)
{
    std::lock_guard<std::mutex> lg(mut);
    Node<Type>* head(new Node<Type>(m_top.m_value, m_top.m_prev));
    m_top.m_value = value;
    m_top.m_prev = head;
    ++m_size;
}

template <typename Type>
Type Stack<Type>::pop()
{
    std::lock_guard<std::mutex> lg(mut);
    if (isEmpty()) { 
        throw std::out_of_range("Stack is empty"); 
    }
    Type value = m_top.m_value;
    Node<Type>* tmp = m_top.m_prev;
    if (tmp == &m_end) {
        m_top.m_prev == &m_end;
    } else {
        m_top.m_value = tmp->m_value;
        m_top.m_prev = tmp->m_prev;
        delete tmp;
    }
    --m_size;
    return value;
}

template <typename Type>
Type Stack<Type>::peek()
{
    std::lock_guard<std::mutex> lg(mut);
    if (m_size) return m_top.m_value;
    else throw std::out_of_range("Stack is empty");
}