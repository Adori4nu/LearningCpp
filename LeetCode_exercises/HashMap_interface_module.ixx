module;

#include <iostream>
#include <string>
#include <string_view>

export module Hash_Map; // Unordered Map
#pragma region Underlying Node based collision storage
export template <typename Type>
class NodeHashMap {
    struct Node {
        std::string key{};
        Type value{};
        Node* next{nullptr};

        Node() = default;
        explicit Node(std::string_view key, const Type& value) : key{key}, value{value}, next{nullptr} {}

        friend std::ostream& operator<<(std::ostream& os, const Node* node)
        {
            if (node == nullptr) {
                os << "[ address: 0x" << std::hex << 0
                   << std::dec << ", key: none"
                   << ", value: none"
                   << ", next: 0x0 ]";
                return os;
            }
            
            os << "[ address: 0x" << std::hex << reinterpret_cast<uintptr_t>(node)
               << std::dec << ", key: " << node->key
               << ", value: " << node->value
               << ", next: 0x" << std::hex << reinterpret_cast<uintptr_t>(node->next)
               << " ]" << std::dec;
            return os;
        }
    };

    auto hash(std::string_view key) const -> size_t {
        size_t hash{};
        for (char c : key) {
            hash = (hash * 31) + c;
        }
        return hash;
    }

    static constexpr size_t M_SIZE = 13;
    Node* m_dataMap[M_SIZE]{};
    size_t m_size{0};

public:

    NodeHashMap() = default;
    explicit NodeHashMap(std::string_view key, const Type& value) : m_size{1} {
        size_t index{ hash(key) % M_SIZE };
        m_dataMap[index] = new Node{key, value};
    }

    ~NodeHashMap() {
        for (size_t i{0}; i < M_SIZE; ++i) {
            Node* current{ m_dataMap[i] };
            while (current) {
                Node* next{ current->next };
                delete current;
                current = next;
            }
            m_dataMap[i] = nullptr;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const NodeHashMap& storage) {
        os << "[ Node Base Hash Map (Unordered Map) ]\n";
        for (size_t i{0}; i < M_SIZE; ++i) {
            os << "[ Bucket " << i << ": ]";
            Node* current{ storage.m_dataMap[i] };
            while (current) {
                os << "\n\t" << current;
                current = current->next;
            }
            os << "\n";
        }
        return os;
    }
};
#pragma endregion