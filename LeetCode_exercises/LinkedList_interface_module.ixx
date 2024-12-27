module;

#include <iostream>

export module LinkedList;

export template <typename Type>
class LinkedList{
    class Node{
    public:
        Type value;
        Node* next;

        Node(Type value) : value{value}, next{nullptr} {}

        friend std::ostream& operator<<(std::ostream& os, const Node& node)
        {
            os << "[ value: " << node.value << ", next: " << reinterpret_cast<void*>(node.next) << " ]";
            return os;
        }
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
            std::cout << "Deleting node with value: [ " << current->value << " ]\n";
            delete current;
            current = m_head;
        }
    }

    auto append(Type value) -> void;
    auto deleteLast() -> void;
    auto prepend(Type value) -> void;
    auto deleteFirst() -> void;
    auto insert(size_t index, Type value) -> bool;
    auto deleteNode(size_t index) -> void;
    auto reverse() -> void;
    
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

    typename LinkedList<Type>::Node* get(size_t index);
    Type& getHead() { return m_head->value; }
    const Type& getHead() const { return m_head->value; }
    Type& getTail() { return m_tail->value; }
    const Type& getTail() const { return m_tail->value; }
    size_t getLenght() const { return m_size; }
    
    bool set(int index, int value);
};

export template <typename Type>
LinkedList(Type) -> LinkedList<Type>; // deduction guide probably not needed in c++23 with my usage scenarios

export template <typename Type>
auto LinkedList<Type>::append(Type value) -> void
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

export template <typename Type>
auto LinkedList<Type>::deleteLast() -> void
{
    if (m_size == 0) return;
    Node* current{ m_head };
    if (m_size == 1) {
        m_head = m_tail = nullptr;
    } else {
        Node* slow{ m_head };
        while (current->next)
        {
            slow = current;
            current = current->next;
        }
        m_tail = slow; 
        m_tail->next = nullptr;
    }
    delete current;
    --m_size;
}

export template <typename Type>
auto LinkedList<Type>::prepend(Type value) -> void
{
    Node* temp{ new Node{ value } };
    if (m_size >= 1)
    {
        temp->next = m_head;
        m_head = temp;
    } else {
        m_head = m_tail = temp;
    }
    ++m_size;
}

export template <typename Type>
auto LinkedList<Type>::deleteFirst() -> void
{
    if (m_size == 0) return;
    Node* temp{ m_head };
    if (m_size > 1)
    {
        m_head = m_head->next;
    } else {
        m_head = m_tail = nullptr;
    }
    delete temp;
    --m_size;
}

export template <typename Type>
auto LinkedList<Type>::insert(size_t index, Type value) -> bool
{
    if (index < 0 || index > m_size) return false;
    if (index == 0) {
        prepend(value);
        return true;
    }
    if (index == m_size) {
        append(value);
        return true;
    }
    Node* new_node{ new Node{ value } };
    Node* temp{ get(index - 1) };
    new_node->next = temp->next;
    temp->next = new_node;
    ++m_size;
    return true;
}

export template <typename Type>
auto LinkedList<Type>::deleteNode(size_t index) -> void
{
    if (index < 0 || index >= m_size) return; 
    if (index == 0) return deleteFirst();
    if (index == m_size - 1) return deleteLast();

    Node* slow{ get(index - 1) };
    Node* temp{ slow->next };

    slow->next = temp->next;
    delete temp;
    --m_size;
}

export template <typename Type>
auto LinkedList<Type>::reverse() -> void
{
    if (m_size == 0 || m_size == 1) return;
    Node* temp{ m_head };
    m_head = m_tail;
    m_tail = temp;
    Node* slow{ nullptr };
    Node* fast{ temp->next };
    for (size_t i{ 0 }; i < m_size; ++i) {
        fast = temp->next;
        temp->next = slow;
        slow = temp;
        temp = fast;
    }
}

export template <typename Type>
typename LinkedList<Type>::Node* LinkedList<Type>::get(size_t index)
{
    if (index < 0 || index >= m_size) return nullptr;
    Node* temp{ m_head };
    while (index > 0)
    {
        temp = temp->next;
        --index;
    }
    return temp;
}

export template <typename Type>
bool LinkedList<Type>::set(int index, int value)
{
    Node* temp{ get(index) };
    if (temp) {
        temp->value = value;
        return true;
    }
    return false;
}
