module;

#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

export module Set; // keys only no duplicates
namespace myjunk::internal
{
    template <typename KeyType>
    struct Set_Node {
        KeyType key{};
        Set_Node* next{nullptr};

        Set_Node() = default;
        explicit Set_Node(const KeyType& key) : key{key}, next{nullptr} {}

        friend std::ostream& operator<<(std::ostream& os, const Set_Node* node)
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

    template <>
    struct Set_Node<std::string_view> {
        std::string key{};
        Set_Node* next{nullptr};

        Set_Node() = default;
        explicit Set_Node(std::string_view key) : key{key}, next{nullptr} {}

        friend std::ostream& operator<<(std::ostream& os, const Set_Node* node)
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
    template <>
    struct Set_Node<int> {
        int key{};
        Set_Node* next{nullptr};

        Set_Node() = default;
        explicit Set_Node(int key) : key{key}, next{nullptr} {}

        friend std::ostream& operator<<(std::ostream& os, const Set_Node* node)
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

    template <typename KeyType>
    inline auto hash(const KeyType& key) -> size_t {
        return std::hash<KeyType>{}(key);
    }

    inline auto hash(int key) -> size_t {
       uint32_t h{ static_cast<uint32_t>(key) };

        h ^= h >> 16;
        h *= 0x85ebca6b;
        h ^= h >> 13;
        h *= 0xc2b2ae35;
        h ^= h >> 16;

        return h;
    }

    inline auto hash(std::string_view key) -> size_t {
        size_t hash{};
        for (char c : key) {
            hash = (hash * 31) + c;
        }
        return hash;
    }
}

export namespace myjunk
{
    #pragma region Node based collision storage
    template <typename KeyType>
    class NodeSet {
        using Node = internal::Set_Node<KeyType>;
    
        static constexpr float MAX_LOAD_FACTOR = 0.75f;
        size_t m_bucketCount{};
        Node** m_dataMap{};
        size_t m_size{0};
    
    public:
    
        explicit NodeSet(size_t bucket_count = 8)
         : m_bucketCount{ bucket_count }, m_dataMap{ new Node*[m_bucketCount]()} {}
    
        template <typename K>
        NodeSet(K&& key, size_t bucket_count = 8)
         : m_bucketCount{ bucket_count }, m_dataMap{ new Node*[m_bucketCount]()}, m_size{1} {
            size_t index{ get_index(std::forward<K>(key)) };
            m_dataMap[index] = new Node{ std::forward<K>(key) };
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

        NodeSet(const NodeSet& other)
         : m_bucketCount{ other.m_bucketCount }
         , m_dataMap{ new Node*[other.m_bucketCount]() }
         , m_size{ other.m_size } {
            for (size_t i{0}; i < m_bucketCount; ++i) {
                if (other.m_dataMap[i]) {
                    m_dataMap[i] = new Node(*other.m_dataMap[i]);

                    Node* src_current = other.m_dataMap[i]->next;
                    Node* dest_current = m_dataMap[i];

                    while (src_current) {
                        dest_current->next = new Node{ *src_current };
                        dest_current = dest_current->next;
                        src_current = src_current->next;
                    }
                }
            }
        }

        NodeSet& operator=(const NodeSet& other) {
            if (this != &other) {
                this->~NodeSet();

                new (this) NodeSet(other);
            }
            return *this;
        }

        NodeSet(NodeSet&& other) noexcept {
            m_bucketCount = other.m_bucketCount;
            m_dataMap = other.m_dataMap;
            m_size = other.m_size;

            other.m_dataMap = nullptr;
            other.m_bucketCount = 0;
            other.m_size = 0;
        }
    
        NodeSet& operator=(NodeSet&& other) noexcept {
            if (this != &other) {
                this->~NodeSet();

                m_bucketCount = other.m_bucketCount;
                m_dataMap = other.m_dataMap;
                m_size = other.m_size;

                other.m_dataMap = nullptr;
                other.m_bucketCount = 0;
                other.m_size = 0;
            }
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& os, const NodeSet& storage) {
            os << "[ Node Base Set ]\n";
            if (storage.size() == 0) return os << "[]";
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
    
        auto load_factor() const -> float {
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
    
                    insert(current->key);
    
                    current->next = nullptr;
                    delete current;
    
                    current = current->next;
                }
            }
    
            delete[] old_data_map;
        }
    
        auto insert(const KeyType& key) -> void {
            size_t index{ get_index(key) };
    
            if (!m_dataMap[index]) {
                m_dataMap[index] = new Node(key);
                ++m_size;
                check_and_rehash();
                return;
            }
    
            Node* current{ m_dataMap[index] };
            if (current->key == key) return;
    
            while (current->next) {
                current = current->next;
                if (current->key == key) return;
            }
    
            current->next = new Node(key);
            ++m_size;
            check_and_rehash();
        }
    
        auto find(const KeyType& key) -> KeyType* {
            size_t index{ get_index(key) };
            Node* current{ m_dataMap[index] };
            while (current) {
                if (current->key == key) return &current->key;
                current = current->next;
            }
            return nullptr;
        }

        auto erase(const KeyType& key) -> bool {
            size_t index{ get_index(key) };

            if (!m_dataMap[index]) return false;

            
            Node* current{ m_dataMap[index] };
            if (current->key == key) {
                m_dataMap[index] = current->next;
                delete current;
                --m_size;
                return true;
            }

            while (current->next) {
                if (current->next->key == key) {
                    Node* to_delete{ current->next };
                    current->next = to_delete->next;
                    delete to_delete;
                    --m_size;
                    return true;
                }
                current = current->next;
            }
            return false;
        }
    
        auto keys() -> std::vector<KeyType> {
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
        size_t get_index(const KeyType& key) const { return internal::hash(key) % m_bucketCount; }
        
        size_t getBucketCount() const { return m_bucketCount; }
        const Node* getBucketHead(size_t bucket) const { return m_dataMap[bucket]; }
    };
    #pragma endregion
}