module;

#include <iostream>

export module Doubly_LL;

#pragma region Doubly Linked List declaration and basic functions
export template <typename Type>
class Doubly_LinkedList
{
    class Node{
    public:
        Type value{};
        Node* next{nullptr};
        Node* prev{nullptr};

        Node() = default;
        Node(Type value) : value{value}, next{nullptr}, prev{nullptr} {}

        friend std::ostream& operator<<(std::ostream& os, const Node& node)
        {
            os << "[ value: " << node.value
             << ", next: " << reinterpret_cast<void*>(node.next)
             << ", prev: " << reinterpret_cast<void*>(node.prev)
             << " ]";
            return os;
        }
    };

    Node* m_head;
    Node* m_tail;
    size_t m_size{};

public:

    Doubly_LinkedList<Type>() : m_head{nullptr}, m_tail{nullptr}, m_size{0} {}
    Doubly_LinkedList<Type>(Type value) : m_head{new Node(value)}, m_tail{m_head}, m_size{1} {}

    ~Doubly_LinkedList()
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

    friend std::ostream& operator<<(std::ostream& os, const Doubly_LinkedList<Type>& list)
    {
        typename Doubly_LinkedList<Type>::Node* current{ list.m_head };
        os << "[ head -> next: ";
        while (current) {
            os << current->value;
            if (current->next) {
                os << " -> ";
            }
            current = current->next;
        }
        os << " ]\n";
        os << "[ tail -> prev: ";
        current = list.m_tail;
        while (current) {
            os << current->value;
            if (current->prev) {
                os << " -> ";
            }
            current = current->prev;
        }
        os << " ]";
        return os;
    }

    Type& getHead() { return m_head->value; }
    const Type& getHead() const { return m_head->value; }
    Type& getTail() { return m_tail->value; }
    const Type& getTail() const { return m_tail->value; }
    size_t size() const { return m_size; }
    
    using NodePtr = Node*;
    typename Doubly_LinkedList<Type>::Node* get(size_t index);
    auto set(size_t index, Type value) -> bool;
    auto insert(size_t index, Type value) -> bool;
    auto deleteNode(size_t index) -> void;
    auto swapFirstLast() -> void;
    auto reverse() -> void;
    auto isPalindrome() -> bool;
    auto swapPairs() -> void;
};
#pragma endregion
#pragma region Doubly Linked List implementation and more complex functionality

export template <typename Type>
Doubly_LinkedList(Type) -> Doubly_LinkedList<Type>;

export template <typename Type>
auto Doubly_LinkedList<Type>::append(Type value) -> void
{
    Node* temp{ new Node{value} };
    if (m_size == 0)
    {
        m_head = m_tail = temp;
    }
    else
    {
        m_tail->next = temp;
        temp->prev = m_tail;
        m_tail = temp;
    }
    ++m_size;
}

export template <typename Type>
auto Doubly_LinkedList<Type>::deleteLast() -> void
{
    if (m_size == 0) return;
    Node* current{ m_tail };
    if (m_size == 1) {
        m_head = m_tail = nullptr;
    } else {
        m_tail = m_tail->prev;
        m_tail->next = nullptr;
    }
    delete current;
    --m_size;
}

export template <typename Type>
auto Doubly_LinkedList<Type>::prepend(Type value) -> void
{
    Node* temp{ new Node{ value } };
    if (m_size == 0) {
        m_head = m_tail = temp;
    } else {
        temp->next = m_head;
        m_head->prev = temp;
        m_head = temp;
    }
    ++m_size;
}

export template <typename Type>
auto Doubly_LinkedList<Type>::deleteFirst() -> void
{
    if (m_size == 0) return;
    Node* temp{ m_head };
    if (m_size == 1) {
        m_head = m_tail = nullptr;
    } else {
        m_head = m_head->next;
        m_head->prev = nullptr;
    }
    delete temp;
    --m_size;
}

export template <typename Type>
typename Doubly_LinkedList<Type>::Node *Doubly_LinkedList<Type>::get(size_t index)
{
    if (index < 0 || index >= m_size) return nullptr;
    Node* temp{ (index < m_size / 2) ? m_head : m_tail };
    if (index < m_size / 2) {
        for (size_t i{ 0 }; i < index; ++i) {
            temp = temp->next;
        }
    } else {
        for (size_t i{ m_size - 1 }; i > index; --i) {
            temp = temp->prev;
        }
    }
    return temp;
}

export template <typename Type>
auto Doubly_LinkedList<Type>::set(size_t index, Type value) -> bool
{
    Node* temp{ get(index) };
    if (temp) {
        temp->value = value;
        return true;
    }
    return false;
}

export template <typename Type>
auto Doubly_LinkedList<Type>::insert(size_t index, Type value) -> bool
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

    Node* newNode{ new Node(value) };
    Node* before{ get(index - 1) };
    Node* after{ before->next };

    newNode->prev = before;
    newNode->next = after;
    before->next = newNode;
    after->prev = newNode;
    ++m_size;

    return true;
}

export template <typename Type>
auto Doubly_LinkedList<Type>::deleteNode(size_t index) -> void
{
    if (index < 0 || index >= m_size) return;
    if (index == 0) {
        return deleteFirst();
    }
    if (index == m_size - 1) {
        
        return deleteLast();
    }

    Node* temp{ get(index) };
    /* Readable version */
    // Node* before{ temp->prev };
    // Node* after{ temp->next };
    
    // before->next = after;
    // after->prev = before;

    /* Optimized for space */
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

    delete temp;
    --m_size;
}

template <typename Type>
auto Doubly_LinkedList<Type>::swapFirstLast() -> void
{
    if (m_size < 2) return;
    if (m_size == 2) {
        m_tail = m_head;
        m_head = m_head->next;
        m_head->prev = nullptr;
        m_tail->next = nullptr;
        m_tail->prev = m_head;
        m_head->next = m_tail;
        return;
    }
    Node* temp{ m_head };
    
    m_head->next->prev = m_tail;
    m_tail->prev->next = m_head;

    m_tail->next = m_head->next;
    m_head->prev = m_tail->prev;

    m_head->next = nullptr;
    m_tail->prev = nullptr;
    
    m_head = m_tail;
    m_tail = temp;
}

export template <typename Type>
auto Doubly_LinkedList<Type>::reverse() -> void
{
    if (m_size < 2) return;
    
    Node* temp = m_head;
    if (m_size == 2) {
        m_head = m_tail;
        m_tail = temp;
        m_head->next = m_tail;
        m_head->prev = nullptr;
        m_tail->prev = m_head;
        m_tail->next = nullptr;
        return;
    }
    
    Node* current = m_head;
    temp = nullptr;
    
    while (current) {
        temp = current->next;
        
        current->next = current->prev;
        current->prev = temp;
        
        current = temp;
    }
    
    temp = m_head;
    m_head = m_tail;
    m_tail = temp;
}

export template <typename Type>
auto Doubly_LinkedList<Type>::isPalindrome() -> bool
{
    if (m_size < 0) return false;
    if (m_size == 0 || m_size == 1) return true;

    Node* forwardNode{ m_head };
    Node* backwardNode{ m_tail };

    for (int i{ 0 }; i < m_size / 2; ++i) {
        if (forwardNode->value != backwardNode->value)
            return false;
        forwardNode = forwardNode->next;
        backwardNode = backwardNode->prev;
    }

    return true;
}

template <typename Type>
auto Doubly_LinkedList<Type>::swapPairs() -> void
{
    if (m_size < 2) return;

    Node* current{ m_head };
    Node* newHead{ m_head->next };

    while (current && current->next) {
        Node* first{ current };
        Node* second{ current->next };
        Node* nextPair{ current->next->next };

        second->prev = first->prev;
        first->next = nextPair;
        first->prev = second;
        second->next = first;

        if (second->prev) {
            second->prev->next = second;
        }

        if (nextPair) {
            nextPair->prev = first;
        }

        current = nextPair;
    }

    m_head = newHead;
    if (m_size % 2 == 0) {
        m_tail = m_tail->prev;
    }
}

#pragma endregion