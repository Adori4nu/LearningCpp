module;

#include <iostream>

export module Stack;
#pragma region Underlying Node based storage
template <typename Type>
class ListStorage{
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
    
    Node* m_top{nullptr};
    size_t m_size{};

public:

    ListStorage() = default;
    explicit ListStorage(const Type& value) : m_top{new Node(value)}, m_size{1} {}

    ~ListStorage() {
        std::cout << "[ List based Stack ]\n";
        Node* current{m_top};
        while (m_top)
        {
            m_top = m_top->next;
            std::cout << "Deleting node with value: [ " << current->value << " ]\n";
            delete current;
            current = m_top;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const ListStorage& storage) {
        Node* current = storage.m_top;
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

    auto push(const Type& value) -> void {
        auto* new_node{ new Node(value) };
        new_node->next = m_top;
        m_top = new_node;
        ++m_size;
    }

    auto pop() -> void {
        if (m_size <= 0) return;

        Node* temp{ m_top };
        m_top = m_top->next;
        delete temp;
        --m_size;
    }

    Type& top() { return m_top->value; }
    const Type& top() const { return m_top->value; }

    bool empty() const { return m_size == 0; }
    size_t size() const { return m_size; }
};
#pragma endregion
#pragma region Underlying Dynnamic Array based storage
template <typename Type>
class VectorStorage {
    static constexpr size_t INITIAL_CAPACITY = 10;
    Type* m_data{nullptr};
    size_t m_size{};
    size_t m_capacity{};

    Type* allocate(size_t new_capacity) {
        void* raw{::operator new(new_capacity * sizeof(Type))};
        return static_cast<Type*>(raw);
    }

    void deallocate(Type* ptr) {
        ::operator delete(ptr);
    }

    void destroy_elements(Type* start, Type* end) {
        std::cout << "[ Vector based Stack ]\n";
        while (start != end) {
            std::cout << "Deleting element with value: [ " << *start << " ]\n";
            start->~Type();
            ++start;
        }
    }

public:

    VectorStorage() : m_data{allocate(INITIAL_CAPACITY)}, m_capacity{INITIAL_CAPACITY} {}

    explicit VectorStorage(const Type& value)
        : m_data{allocate(INITIAL_CAPACITY)}
        , m_capacity(INITIAL_CAPACITY)
        , m_size{1} {
        new(m_data) Type(value);
    }

    ~VectorStorage() {
        destroy_elements(m_data, m_data + m_size);
        deallocate(m_data);
    }

    friend std::ostream& operator<<(std::ostream& os, const VectorStorage& storage) {
        os << "[ top: ";
        for (size_t i{ storage.m_size}; i > 0; --i) {
            os << storage.m_data[i - 1];
            if (i > 1) {
                os << " -> ";
            }
        }
        os << " ]\n";
        return os;
    }

    auto push(const Type& value) -> void {
        if (m_size == m_capacity) {
            size_t new_capacity{ m_capacity * 2 };
            std::cout << "Resizing from " << m_capacity << " to " << new_capacity << "\n";
            Type* new_data{ allocate(new_capacity) };

            // Move existing elements using placement new
            for (size_t i{0}; i < m_size; ++i) {
                new(new_data + i) Type(std::move(m_data[i]));
                m_data[i].~Type(); // Destroy old elements
            }

            deallocate(m_data);
            m_data = new_data;
            m_capacity = new_capacity;
        }
        std::cout << "Pushing value: [ " << value << " ]\n";
        // Construct new element in place
        new(m_data + m_size) Type(value);
        ++m_size;
    }

    auto pop() -> void {
        if (m_size > 0) {
            std::cout << "Popping value: [ " << m_data[m_size - 1] << " ]\n";
            m_data[m_size - 1].~Type();
            --m_size;
        }
    }

    Type& top() { return m_data[m_size - 1]; }
    const Type& top() const { return m_data[m_size - 1]; }

    bool empty() const { return m_size == 0; }
    size_t size() const { return m_size; }
};
#pragma endregion
#pragma region Stack declaration
export template <typename Type, template <typename> typename Storage = ListStorage>
class Stack{

    Storage<Type> m_storage;    

public:

    Stack() = default;
    Stack(const Type& value) : m_storage{value} {}

    friend std::ostream& operator<<(std::ostream& os, const Stack& stack) {
        return os << stack.m_storage;
    }

    Type& top() { return m_storage.top(); }
    const Type& top() const { return m_storage.top(); }

    bool empty() const { return m_storage.empty(); }
    size_t size() const { return m_storage.size(); }

    auto push(const Type& value) -> void { m_storage.push(value); }
    auto pop() -> void { m_storage.pop(); }

};
#pragma endregion
#pragma region Stack implementation

// helps deduce type when only value of single item is passed to constructor
// but in this case Stack will be node based
export template <typename Type>
Stack(Type) -> Stack<Type, ListStorage>;

export template<typename Type>
using VectorBase = VectorStorage<Type>;

export template<typename Type>
using NodeBasedStack = Stack<Type, ListStorage>;

export template<typename Type>
using VectorBasedStack = Stack<Type, VectorStorage>;

#pragma endregion