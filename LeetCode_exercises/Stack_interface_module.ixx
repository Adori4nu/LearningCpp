module;

#include <iostream>

export module Stack;
#pragma region Stack declaration
export template <typename Type>
class Stack{
    class Node {
    public:
        Type value{};
        Node* next{nullptr};

        Node() = default;
        Node(Type value) : value{value}, next{nullptr} {};

        friend std::ostream& operator<<(std::ostream& os, const Node& node)
        {
            os << "[ value: " << node.value << ", next: " << reinterpret_cast<void*>(node.next) << " ]";
        }
    };

    Node* m_top{nullptr};
    size_t m_size{};

public:
    Stack<Type>() : m_top{nullptr}, m_size{0} {}
    Stack(Type value) : m_top{new Node(value)}, m_size{1} {}

    ~Stack()
    {
        Node* current{m_top};
        while (m_top)
        {
            m_top = m_top->next;
            std::cout << "Deleting node with value: [ " << current->value << " ]\n";
            delete current;
            current = m_top;
        }
        
    }

    friend std::ostream& operator<<(std::ostream& os, const Stack<Type>& stack)
    {
        typename Stack<Type>::Node* current{ stack.m_top };
        os << "[ top: ";
        while (current) {
            os << current->value;
            if (current->next) {
                os << " -> ";
            }
            current = current->next;
        }
        os << " ]\n";
        return os;
    }

    using NodePtr = Node*;
    Type& top() { return m_top->value; }
    const Type& top() const { return m_top->value; }
    size_t size() const { return m_size; }

    auto push(Type value) -> void;
    auto pop() -> void;

};
#pragma endregion
#pragma region Stack implementation

export template <typename Type>
Stack(Type) -> Stack<Type>;

export template <typename Type>
auto Stack<Type>::push(Type value) -> void
{
    Node* temp{ new Node{ value } };
    temp->next = m_top;
    m_top = temp;
    ++m_size;
}

export template <typename Type>
auto Stack<Type>::pop() -> void
{
    if (m_size <= 0) return;

    Node* temp{ m_top };
    m_top = m_top->next;
    delete temp;
    --m_size;
}

