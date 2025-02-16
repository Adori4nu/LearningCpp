module;

#include <iostream>
#include <string>

export module Queue;
#pragma region List Storage backend implementation
template <typename Type>
class QueListStorage {
    struct Node {
            Type value{};
            Node* next{nullptr};
    
            Node() = default;
            explicit Node(const Type& value) : value{value}, next{nullptr} {};
    
            friend std::ostream& operator<<(std::ostream& os, const Node* node)
            {
                os << "[ address: 0x" << std::hex << reinterpret_cast<uintptr_t>(node)
                << " value: "  << std::dec << (node == nullptr ? "none" : std::to_string(node->value))
                << ", next: 0x" << std::hex << (node == nullptr ? 0 : reinterpret_cast<uintptr_t>(node->next))
                << " ]" << std::dec;
                return os;
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

    friend std::ostream& operator<<(std::ostream& os, const QueListStorage& storage) {
        Node* current{ storage.m_back };
        os << "[ end: ";
        while (current) {
            os << current->value;
            if (current->next) {
                os << " -> ";
            }
            current = current->next;
        }
        os << " :start ]\n";
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
    static constexpr size_t INITIAL_CAPACITY = 8;
    Type* m_data{nullptr};
    size_t m_size{};
    size_t m_start_index{};
    size_t m_capacity{};

    Type* allocate(size_t new_capacity) {
        void* raw{ ::operator new(new_capacity * sizeof(Type)) };
        return static_cast<Type*>(raw);
    }

    void deallocate(Type* ptr) {
        ::operator delete(ptr);
    }

    void destroy_elements(Type* start, Type* end) {
        std::cout << "[ Vector based Queue ]\n";
        while (start != end) {
            std::cout << "Deleting element with value: [" << *start << " ]\n";
            start->~Type();
            ++start;
        }
    }

public:

    QueVectorStorage() : m_data{allocate(INITIAL_CAPACITY)}, m_capacity{INITIAL_CAPACITY} {}

    explicit QueVectorStorage(const Type& value)
    : m_data{allocate(INITIAL_CAPACITY)}
    , m_capacity(INITIAL_CAPACITY)
    , m_size{1} {
        new(m_data) Type(value);
    }

    ~QueVectorStorage() {
        destroy_elements(m_data, m_data + m_size);
        deallocate(m_data);
    }

    friend std::ostream& operator<<(std::ostream& os, const QueVectorStorage& storage) {
        os << "[ end: ";
        for (size_t i{ storage.m_size }; i > 0; --i) {
            size_t index{ (storage.m_start_index + i - 1) % storage.m_capacity };
            os << storage.m_data[index];
            if (i >  1) {
                os << " -> ";
            }
        }
        os << " :start ]\n";
        return os;
    }

    bool empty() { return m_size == 0; }
    size_t size() { return m_size; }

    Type& front() { return m_data[m_start_index]; }
    const Type& front() const { return m_data[m_start_index]; }
    Type& back() { return m_data[ (m_start_index + m_size - 1) % m_capacity]; }
    const Type& back() const { return m_data[ (m_start_index + m_size - 1) % m_capacity]; }

    auto push(const Type& value) -> void {
        if (m_size == m_capacity) {
            size_t new_capacity{ m_capacity * 2 };
            std::cout << "Resizing from " << m_capacity << " to " << new_capacity << "\n";
            Type* new_data{ allocate(new_capacity) };

            // calculating old index because we store
            // start point that gets modiffied when we
            // pop element form front of que
            for (size_t i{0}; i < m_size; ++i) {
                size_t old_index{ (m_start_index + i) % m_capacity };
                new(new_data + i) Type(std::move(m_data[old_index]));
                m_data[old_index].~Type();
            }

            deallocate(m_data);
            m_data = new_data;
            m_capacity = new_capacity;
            m_start_index = 0;
        }

        size_t insert_pos{ (m_start_index + m_size) % m_capacity };
        new(m_data + insert_pos) Type(value);
        ++m_size;
    }

    auto pop() -> void {
        if (m_size > 0) {
            // Destroy the element at start index
            m_data[m_start_index].~Type();
            
            m_start_index = (m_start_index + 1) % m_capacity;
            --m_size;
        }
    }

};
#pragma endregion
#pragma region Queue declaration
export template <typename Type, template <typename> typename Storage = QueListStorage>
class Queue {
    
    Storage<Type> m_storage;

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
Queue(Type) -> Queue<Type, QueListStorage>;

export template<typename Type>
using VecForQ = QueVectorStorage<Type>;

export template<typename Type>
using NodeBaseQue = Queue<Type, QueListStorage>;

export template<typename Type>
using VecBaseQue = Queue<Type, QueVectorStorage>;

#pragma endregion

