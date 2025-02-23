module;

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

export module Hash_Map; // Unordered Map
namespace myjunk::internal
{
    #pragma region Hash Map Node
    template <typename Type>
    struct Hash_Node {
        std::string key{};
        Type value{};
        Hash_Node* next{nullptr};
    
        Hash_Node() = default;
        explicit Hash_Node(std::string_view key, const Type& value) : key{key}, value{value}, next{nullptr} {}
    
        friend std::ostream& operator<<(std::ostream& os, const Hash_Node* node)
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

    inline auto hash(std::string_view key) -> size_t {
        size_t hash{};
        for (char c : key) {
            hash = (hash * 31) + c;
        }
        return hash;
    }
    #pragma endregion
};
export namespace myjunk
{
    #pragma region Map Node based collision storage
    template <typename Type>
    class NodeMap {
        using Node = internal::Hash_Node<Type>;

        static constexpr float MAX_LOAD_FACTOR = 0.75f;
        size_t m_bucketCount{};
        Node** m_dataMap{};
        size_t m_size{0};

    public:
        
        explicit NodeMap(size_t bucket_count = 16)
         : m_bucketCount{bucket_count}, m_dataMap{ new Node*[m_bucketCount]()} {}

        explicit NodeMap(std::string_view key, const Type& value, size_t bucket_count = 16)
         : m_bucketCount{bucket_count}, m_dataMap{ new Node*[m_bucketCount]()}, m_size{1} {
            size_t index{ get_index(key) };
            m_dataMap[index] = new Node{key, value};
        }
        
        ~NodeMap() {
            for (size_t i{0}; i < m_bucketCount; ++i) {
                Node* current{ m_dataMap[i] };
                while (current) {
                    Node* next{ current->next };
                    delete current;
                    current = next;
                }
            }
            delete[] m_dataMap;
            m_dataMap = nullptr;
            m_size = 0;
        }

        friend std::ostream& operator<<(std::ostream& os, const NodeMap& storage) {
            os << "[ Node Base Hash Map (Unordered Map) ]\n";
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

            for (size_t i{0}; i < old_bucket_count; ++i) {
                Node* current{ old_data_map[i] };
                while (current) {
                    Node* next{ current->next };

                    set(current->key, current->value);

                    current->next = nullptr;
                    delete current;

                    current = next;
                }
            }

            delete[] old_data_map;
        }

        auto set(std::string_view key, const Type& value) -> void {
            size_t index { get_index(key) };
            
            if (!m_dataMap[index]) {
                m_dataMap[index] = new Node(key, value);
                ++m_size;
                check_and_rehash();
                return;
            }

            Node* current{ m_dataMap[index] };
            while (current->next) {
                if (current->key == key) {
                    current->value = value;
                    return;
                }
                current = current->next;
            }

            current->next = new Node(key, value);
            ++m_size;
            check_and_rehash();
        }

        auto find(std::string_view key) -> Type* {
            size_t index{ get_index(key) };
            Node* current{ m_dataMap[index] };
            while (current) {
                if (current->key == key) return &current->value;
                current = current->next;
            }
            return nullptr;
        }
    
        auto keys() -> std::vector<std::string_view> {
            std::vector<std::string_view> all_keys;
            for (size_t i{ 0 }; i < m_bucketCount; ++i) {
                Node* current{ m_dataMap[i] };
                while (current) {
                    all_keys.push_back(current->key);
                    current = current->next;
                }
            }
            return all_keys;
        }

        bool empty() const { return m_size == 0; }
        size_t size() const { return m_size; }
        size_t get_index(std::string_view key) const { return internal::hash(key) % m_bucketCount; }
    };
    #pragma endregion
    #pragma region Multi Map Node based collision storage
    template <typename Type>
    class NodeMultiMap {
        using Node = internal::Hash_Node<Type>;
    
        static constexpr float MAX_LOAD_FACTOR = 0.75f;
        size_t m_bucketCount{};
        Node** m_dataMap{};
        size_t m_size{0};
    
    public:
    
        explicit NodeMultiMap(size_t bucket_count = 16)
         : m_bucketCount{bucket_count}, m_dataMap{ new Node*[m_bucketCount]()} {}
    
        explicit NodeMultiMap(std::string_view key, const Type& value, size_t bucket_count = 16)
         : m_bucketCount{bucket_count}, m_dataMap{ new Node*[m_bucketCount]()}, m_size{1} {
            size_t index{ get_index(key) };
            m_dataMap[index] = new Node{key, value};
        }
    
        ~NodeMultiMap() {
            for (size_t i{0}; i < m_bucketCount; ++i) {
                Node* current{ m_dataMap[i] };
                while (current) {
                    Node* next{ current->next };
                    delete current;
                    current = next;
                }
            }
            delete[] m_dataMap;
            m_dataMap= nullptr;
            m_size = 0;
        }
    
        friend std::ostream& operator<<(std::ostream& os, const NodeMultiMap& storage) {
            os << "[ Node Base Hash Map (Unordered Multi Map) ]\n";
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
    
            // Store old data
            Node** old_data_map = m_dataMap;
            size_t old_bucket_count = m_bucketCount;
    
            // Create new empty hash map with increased size
            m_bucketCount = new_bucket_count;
            m_dataMap = new Node*[m_bucketCount]();
            m_size = 0;
    
            // iterate over old map and set old map values in new map
            for (size_t i{0}; i < old_bucket_count; ++i) {
                Node* current{ old_data_map[i] };
                while (current) {
                    Node* next{ current->next };
                    
                    // Re-hash and insert the node
                    set(current->key, current->value);
                    
                    // Delete the old node
                    current->next = nullptr;
                    delete current;
    
                    current = next;
                }
            }
    
            delete[] old_data_map;
        }
    
        auto set(std::string_view key, const Type& value) -> void {
            size_t index{ get_index(key) };
        
            if (!m_dataMap[index]) {
                m_dataMap[index] = new Node(key, value);
                ++m_size;
                check_and_rehash();
                return;
            }
        
            Node* current{ m_dataMap[index] };
            
            while (current->next) {
                current = current->next;
            }
            
            current->next = new Node(key, value);
            ++m_size;
            check_and_rehash();
        }
    
        auto find(std::string_view key) -> std::vector<Type> {
            std::vector<Type> values;
            size_t index{ get_index(key) };
            Node* current{ m_dataMap[index] };
            while (current) {
                if (current->key == key) values.push_back(current->value);
                current = current->next;
            }
            return values;
        }
    
        auto keys() -> std::vector<std::string_view> {
            std::vector<std::string_view> all_keys;
            for (size_t i{ 0 }; i < m_bucketCount; ++i) {
                Node* current{ m_dataMap[i] };
                while (current) {
                    all_keys.push_back(current->key);
                    current = current->next;
                }
            }
            return all_keys;
        }
    
        bool empty() const { return m_size == 0; }
        size_t size() const { return m_size; }
        size_t get_index(std::string_view key) const { return internal::hash(key) % m_bucketCount; }
    };
    #pragma endregion
};