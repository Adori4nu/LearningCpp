module;

#include <iostream>

export module Queue;
#pragma region List Storage backend implementation
template <typename Type>
class QueListStorage {
    struct Node {
            Type value{};
            Node* next{nullptr};
    
            Node() = default;
            explicit Node(const Type& value) : value{value}, next{nullptr} {};
    
            friend std::ostream& operator<<(std::ostream& os, const Node& node)
            {
                os << "[ value: " << node.value << ", next: " << reinterpret_cast<void*>(node.next) << " ]";
            }
            
        };
    
    Node* m_front{nullptr};
    Node* m_back{nullptr};
    size_t m_size{};

public:

    QueListStorage() = default;
    explicit QueListStorage(const Type& value) : m_front{new Node(value)}, m_back{m_front}, m_size{1} {} 

    ~QueListStorage() {
        Node* current{ m_back };
        while (m_back)
        {
            m_back = m_back->next;
            std::cout << "Deleting node with value: [ " << current->value << " ]\n";
            delete current;
            current = m_back;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const QueListStorage& stack) {
        Node* current{ Queue.m_back };
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

    auto push(const Type& value) -> void // enqueue
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

    auto pop() -> void // dequeue
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
    // void emplace(Args&&... args) -> void;
};
#pragma endregion
#pragma region Vector Storage backend declaration
template <typename Type>
class QueVectorStorage {
    static constexpr size_t INITIAL_CAPACITY = 10;
    Type* m_data{nullptr};
    size_t m_size{};
    size_t m_capacity{};

    
};
#pragma endregion
#pragma region Queue declaration
export template <typename Type, template <typename> typename Storage = QueListStorage>
class Queue {
    
    Storage m_storage;

public:
    Queue() = default;
    Queue(const Type& value) : m_storage{value} {} 

    friend std::ostream& operator<<(std::ostream& os, const Queue& queue) {
        return os << queue.m_storage;
    }

    bool empty() { return m_storage.empty(); }
    size_t size() { return m_storage.size(); }

    Type& front() { return m_storage.front(); }
    const Type& front() const { return m_storage.front(); }
    Type& back() { return m_storage.back(); }
    const Type& back() const { return m_storage.back(); }

    auto push(const Type& value) -> void { return m_storage.push(); }; // enqueue
    // void emplace(Args&&... args) -> void;
    auto pop() -> void {return m_storage.pop(); }; // dequeue
};
#pragma endregion
#pragma region Queue implementation

export template <typename Type>
Queue(Type) -> Queue<Type>;



#pragma endregion

