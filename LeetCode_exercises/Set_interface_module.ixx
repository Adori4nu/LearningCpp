module;

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

export module Set; // keys only no duplicates
#pragma region Underlying Node based collision storage
export template <typename Type>
class NodeSet {
    struct Node {
        std::string key{};
        Node* next{nullptr};

        Node() = default;
        explicit Node(std::string_view key) : key{key}, next{nullptr} {}

        friend std::ostream& operator<<(std::ostream& os, const Node* node)
        {
            if (node == nullptr) {
                os << "[ address: 0x" << std::hex << 0
                   << std::dec << ", key: none"
                   << ", next: 0x0 ]";
                return os;
            }
            
            os << "[ address: 0x" << std::hex << reinterpret_cast<uintptr_t>(node)
               << std::dec << ", key: " << node->key
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

    static constexpr float MAX_LOAD_FACTOR = 0.75f;
    size_t m_bucketCount{};
    Node** m_dataMap{};
    size_t m_size{0};

public:

    explicit NodeSet(size_t bucket_count = 13)
     : m_bucketCount{bucket_count}, m_dataMap{ new Node*[m_bucketCount]()} {}

    explicit NodeSet(std::string_view key, size_t bucket_count = 13)
     : m_bucketCount{bucket_count}, m_dataMap{ new Node*[m_bucketCount]()}, m_size{1} {
        size_t index{ hash(key) % m_bucketCount };
        m_dataMap[index] = new Node{key};
    }

    ~NodeSet() {
        for (size_t i{0}; i < m_bucketCount; ++i) {
            Node* current{ m_dataMap[i] };
            while (current) {
                Node* next{ current->next };
                delete current;
                current = next;
            }
            m_dataMap[i] = nullptr;
        }
        delete[] m_dataMap;
        m_size = 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const NodeSet& storage) {
        os << "[ Node Base Set ]\n";
        for (size_t i{0}; i < storage.m_bucketCount; ++i) {
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

    auto check_and_rehash() -> void {
        if (load_factor() >= MAX_LOAD_FACTOR) {
            rehash(m_bucketCount * 2);
        }
    }

    auto load_factor() const -> void {
        return static_cast<float>(m_size) / static_cast<float>(m_bucketCount);
    }

    auto rehash(size_t new_bucket_count) -> void {

        if (new_bucket_count <= m_bucketCount) {
            return;
        }

        Node** old_data_map = m_dataMap;
        size_t old_bucket_count = m_bucketCount;

        m_bucketCount = new_bucket_count;
        m_dataMap = new Node*[m_bucketCount]();
        m_size = 0;

        for(size_t i{0}; i < old_bucket_count; ++i) {
            Node* current{ old_data_map[i] };
            while (current) {
                Node* next{ current->next };

                set(current->key);

                current->next = nullptr;
                delete current;

                current = current->next;
            }
        }

        delete[] old_data_map;
    }

    auto set(std::string_view key) -> void {
        size_t index{ get_index() };

        if (!m_dataMap[index]) {
            m_dataMap[index] = new Node(key);
            ++m_size;
            check_and_rehash();
            return;
        }

        Node* current{ m_dataMap[index] };

        while (current->next) {
            if (current->key == key) return;
            current = current->next;
        }

        current->next = new Node(key);
        ++m_size;
        check_and_rehash();
    }

    auto find(std::string_view key) -> Type* {
        size_t index{ get_index(key) };
        Node* current{ m_dataMap[index] };
        while (current) {
            if (current->key == key) return &current->key;
            current = current->next;
        }
        return nullptr;
    }

    auto keys() -> std::vector<std::string_view> {
        std::vector<std::string_view> all_keys;
        for (size_t i{ 0 }; i < m_bucketCount; ++i) {
            Node* current { m_dataMap[i] };
            while (current) {
                all_keys.push_back(current->key);
                current = current->next;
            }
        }
        return all_keys;
    }

    bool empty() const { return m_size == 0; }
    size_t size() const { return m_size; }
    size_t get_index(std::string_view key) const { return hash(key) % m_bucketCount; }
};
#pragma endregion