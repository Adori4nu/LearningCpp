module;

#include <iostream>
#include <string>

export module Bin_Search_Tree;
#pragma region List Storage backend implementation
export template <typename Type>
class TreeNodeBase{
    struct Node {
        Type value{};
        Node* left{nullptr};
        Node* right{nullptr};

        Node() = default;
        explicit Node(const Type& value) : value{value}, left{nullptr}, right{nullptr} {};

        friend std::ostream& operator<<(std::ostream& os, const Node* node)
        {
            os << "[ address: 0x" << std::hex << reinterpret_cast<uintptr_t>(node)
            << " value: "  << std::dec << (node == nullptr ? "none" : std::to_string(node->value))
            << ", left: 0x" << std::hex << (node == nullptr ? 0 : reinterpret_cast<uintptr_t>(node->left))
            << ", right: 0x" << std::hex << (node == nullptr ? 0 : reinterpret_cast<uintptr_t>(node->right))
            << " ]" << std::dec;
            return os;
        }
        
    };

    Node* m_root{nullptr};
    size_t m_size{};
    
public:

    TreeNodeBase() = default;
    explicit TreeNodeBase(const Type& value) : m_root{new Node(value)}, m_size{1} {}

    ~TreeNodeBase() {
        delete m_root;
    }
};