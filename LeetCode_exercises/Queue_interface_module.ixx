module;

#include <iostream>

export module Queue;
#pragma region Queue declaration
export template <typename Type>
class Queue{
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

    Node* m_front{nullptr};
    Node* m_back{nullptr};
    size_t m_size{};

public:
    Queue() = default;
    Queue(Type value) : m_front{new Node(value)}, m_back{m_front}, m_size{1} {} 

    ~Queue()
    {
        Node* current{ m_back };
        while (m_back)
        {
            m_back = m_back->next;
            std::cout << "Deleting node with value: [ " << current->value << " ]\n";
            delete current;
            current = m_back;
        }
        
    }

    friend std::ostream& operator<<(std::ostream& os, const Queue<Type>& stack)
    {
        typename Queue<Type>::Node* current{ Queue.m_back };
        os << "[ back: ";
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

    bool empty() { return m_size == 0; }
    size_t size() { return m_size; }

    Type& front() { return m_front; }
    const Type& front() const { return m_front; }
    Type& back() { return m_back; }
    const Type& back() const { return m_back; }

    auto push(const Type& value) -> void; // enqueue
    // void emplace(Args&&... args) -> void;
    auto pop() -> void; // dequeue
};
#pragma endregion
#pragma region Queue implementation

export template <typename Type>
Queue(Type) -> Queue<Type>;

export template <typename Type>
auto Queue<Type>::push(const Type &value) -> void
{
    Node* newNode{ new Node(value) };
    if (empty()) {
        m_back = m_front = newNode;
    } else {
        m_back->next = newNode;
        m_back = newNode;
    }
    ++m_size;
}

export template <typename Type>
auto Queue<Type>::pop() -> void
{
    if (m_size == 0) return;
    Node* current{ m_front };
    if (m_size == 1) {
        m_front = m_back = nullptr;
    } else {
        m_front = m_front->next;
    }
    delete current;
    --m_size;
}

#pragma endregion

