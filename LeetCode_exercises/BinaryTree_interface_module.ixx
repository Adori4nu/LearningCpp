module;

#include <iostream>
#include <string>

export module Bin_Search_Tree;
#pragma region List Storage backend implementation
export template <typename Type>
class TreeNodeBase {
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

    void deleteSubtree(Node* node) {
        if (!node) return;

        deleteSubtree(node->left);
        deleteSubtree(node->right);

        std::cout << "Deleting node with value: [ " << node->value << " ]\n";

        delete node;
        --m_size;
    }

    Node* m_root{nullptr};
    size_t m_size{};
    
public:

    TreeNodeBase() = default;
    explicit TreeNodeBase(const Type& value) : m_root{new Node(value)}, m_size{1} {}

    ~TreeNodeBase() {
        std::cout << "\033[1;33m[ Binary Search Tree Destructor ]\033[0m\n";
        deleteSubtree(m_root);
        m_root = nullptr;
        std::cout << "[ Tree size: " << m_size << " ]\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const TreeNodeBase& storage) {
        os << "Tree size: " << storage.m_size << "\n";
        os << "\nValue view: ";
        printValuesRecursive(os, storage.m_root);
        return os << "\n";
    }

    static void printValuesRecursive(std::ostream& os, Node* node) {
        if (node == nullptr) return;
    
        os << "(";
        
        if (node->left) printValuesRecursive(os, node->left);
        os << " " << node->value << " ";
        if (node->right) printValuesRecursive(os, node->right);
        
        os << ")";
    }

    bool empty() { return m_size == 0; }
    size_t size() { return m_size; }

    auto insert(const Type& value) -> bool {
        Node* new_node{ new Node(value) };

        if (empty()) {
            m_root = new_node;
            ++m_size;
            return true;
        } 

        Node* current{ m_root };
        while (current) {
            if (value == current->value) {
                delete new_node;
                return false;
            }

            if (value < current->value) {
                if (!current->left) {
                    current->left = new_node;
                    ++m_size;
                    return true;
                }
                current = current->left;
            } else {
                if (!current->right) {
                    current->right = new_node;
                    ++m_size;
                    return true;
                }
                current = current->right;
            }
        }
        return false;
    }

    auto contains(const Type& value) -> bool {
        Node* current{ m_root };
        while (current) {
            if (value == current->value) return true;

            if (value < current->value) current = current->left;
            else current = current->right;
        }
        return false;
    }

private:

    auto r_contains(Node* current_node, const Type& value) -> bool {
        if (current_node == nullptr) return false;

        if (current_node->value == value) return true;

        if(current_node->value < value) 
            return r_contains(current_node->right, value);
        else 
            return r_contains(current_node->left, value);
    }

    auto r_insert(Node* current_node, const Type& value) -> Node* {
        return Node*{};
    }

public:

    auto r_contains(const Type& value) -> bool {
        return r_contains(m_root, value);
    }

    auto r_insert(const Type& value) -> void {
        r_insert(m_root, value);
    }
};
#pragma endregion