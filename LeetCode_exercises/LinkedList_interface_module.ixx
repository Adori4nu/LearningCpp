module;

#include <iostream>

export module LinkedList;

export template<typename Type>
class LinkedList{
    class Node{
    public:
        Type value;
        Node* next;

        Node(Type value) : value{value}, next{nullptr} {}
    };

    Node* m_head;
    Node* m_tail;
    size_t m_size{};

public:
    LinkedList<Type>() : m_head{nullptr}, m_tail{nullptr}, m_size{0} {}
    LinkedList(Type value) : m_head{new Node(value)}, m_tail{m_head}, m_size{1} {}

    ~LinkedList()
    {
        Node* current{ m_head };
        while (m_head) {
            m_head = m_head->next;
            delete current;
            current = m_head;
        }
    }

    void append(Type value);
    
    friend std::ostream& operator<<(std::ostream& os, const LinkedList<Type>& list)
    {
        typename LinkedList<Type>::Node* current = list.m_head;
        os << "[ ";
        while (current) {
            os << current->value;
            if (current->next) {
                os << " -> ";
            }
            current = current->next;
        }
        os << " ]";
        return os;
    };

    Type& getHead() { return m_head->value; }
    const Type& getHead() const { return m_head->value; }
    Type& getTail() { return m_tail->value; }
    const Type& getTail() const { return m_tail->value; }
    size_t getLenght() const { return m_size; }
};

export template<typename Type>
LinkedList(Type) -> LinkedList<Type>; // deduction guide probably not needed in c++23 with my usage scenarios

export template<typename Type>
void LinkedList<Type>::append(Type value)
{
    Node* temp{ new Node{value} };
    if (m_size == 0)
    {
        m_head = m_tail = temp;
    } 
    else
    {
        m_tail->next = temp;
        m_tail = temp;
    }
    ++m_size;
}