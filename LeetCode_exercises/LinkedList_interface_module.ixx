module;
// #define USE_SET_IMPL
#ifdef USE_SET_IMPL
#include <unordered_set>
#endif
#include <iostream>

export module LinkedList;

export template <typename Type>
class LinkedList{
    class Node{
    public:
        Type value{};
        Node* next{nullptr};

        Node() = default;
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
    auto findMiddleNode() -> Node*;
    auto hasLoop() -> bool;
    auto findKthFromEnd(int k) -> Node*;
    auto partitionList(Type value) -> void;
    auto removeDuplicates() -> void;
    auto binaryToDecimal() -> int;
    auto reverseBetween(int m, int n) -> void;
    
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
    if (m_size == 0) {
        m_head = m_tail = temp;
    } 
    else {
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
    if (m_size >= 1) {
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
    if (m_size > 1) {
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

template <typename Type>
auto LinkedList<Type>::findMiddleNode() -> Node*
{
    Node* fast{ m_head };
    Node* slow{ m_head };
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

export template <typename Type>
auto LinkedList<Type>::hasLoop() -> bool
{   
    Node* fast{ m_head };
    Node* slow{ m_head };
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

export template <typename Type>
auto LinkedList<Type>::findKthFromEnd(int k) -> Node*
{
    if (!m_head) return nullptr;
    Node* fast{ m_head };
    Node* slow{ m_head };
    for (size_t i{ 0 }; i < k; ++i) {
        if (!fast) return nullptr;
        fast = fast->next;
    }
    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}

export template <typename Type>
auto LinkedList<Type>::partitionList(Type value) -> void {
    Node* less{ new Node{} };
    Node* less_tail{ less };
    Node* more_and_equal{ new Node{} };
    Node* more_tail{ more_and_equal };
    Node* current{ m_head };
    while (current) {
        if (current->value < value) {
            less_tail->next = current;
            less_tail = current;
        } else {
            more_tail->next = current;
            more_tail = current;
        }
        current = current->next;
    }
    more_tail->next = nullptr;
    less_tail->next = more_and_equal->next;
    m_head = less->next;
    m_tail = more_tail;
    delete less;
    delete more_and_equal;
}

template <typename Type>
auto LinkedList<Type>::removeDuplicates() -> void
{
#ifndef USE_SET_IMPL
    if (!m_head || !m_head->next) return;
    Node* current{ m_head };
    while(current) {
        Node* prev{ current };
        Node* runner{ current->next };
        while (runner) {
            if (runner->value == current->value) {
                prev->next = runner->next;
                delete runner;
                runner = prev->next;
                --m_size;
            } else {
                prev = runner;
                runner = runner->next;
            }
        }
        current = current->next;
    }
#else
    std::unordered_set<Type> values;
    Node* prev{ nullptr };
    Node* current{ m_head };
    while (current) {
        if (values.find(current->value) != values.end()) {
            prev->next = current->next;
            delete current;
            --m_size;
            current = prev->next;
        } else {
            values.insert(current->value);
            prev = current;
            current = current->next;
        }
    }
#endif
}

template <typename Type>
auto LinkedList<Type>::binaryToDecimal() -> int
{
    uint64_t num{ 0 };
    Node* current{ m_head };
    while (current) {
        num = num * 2 + current->value;
        current = current->next;
    }
    return num;
}

template <typename Type>
auto LinkedList<Type>::reverseBetween(int m, int n) -> void
{
    if (!head || !head->next) return;
    Node* dummy{ new Node(0) };
    dummy->next = head;
    Node* prev{ dummy };
    for (size_t i{ 0 }; i < m; ++i) {
            prev = prev->next;
    }
    Node* current{ prev->next };
    for (size_t i{ 0 }; i < n-m; ++i) {
        Node* ahead{ current->next };
        current->next = ahead->next;
        ahead->next = prev->next;
        prev->next = ahead;
    }
    
    head = dummy->next;
    delete dummy;
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
