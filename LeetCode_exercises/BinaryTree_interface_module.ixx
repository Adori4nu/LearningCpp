module;

#include <iostream>
#include <string>

export module Bin_Search_Tree;

import Queue;
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

    bool empty() const { return m_size == 0; }
    size_t size() const { return m_size; }

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
        delete new_node;
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
        if (!current_node) return new Node{ value };

        if (current_node->value > value) {
            current_node->left = r_insert(current_node->left, value);
        } else if (current_node->value < value) {
            current_node->right = r_insert(current_node->right, value);
        }

        return current_node;
    }

    auto min_val(Node* current_node) -> Type {
        while (current_node->left) {
            current_node = current_node->left;
        }
        return current_node->value;
    }

    auto r_delete(Node* current_node, const Type& value) -> Node* {
        if (!current_node) return nullptr;

        if (value < current_node->value) {
            current_node->left = r_delete(current_node->left, value);
        } else if (value > current_node->value) {
            current_node->right = r_delete(current_node->right, value);
        } else {
            if (!current_node->left && !current_node->right) {
                delete current_node;
                return nullptr;
            } else if (!current_node->left) {
                Node* temp{ current_node->right };
                delete current_node;
                --m_size;
                return temp;
            } else if (!current_node->right) {
                Node* temp{ current_node->left };
                delete current_node;
                --m_size;
                return temp;
            } else {
                Type sub_tree_min{ min_val(current_node->right) };
                current_node->value = sub_tree_min;
                current_node->right = r_delete(current_node->right, sub_tree_min);
            }
        }

        return current_node;
    }

    // pre order means we do operation like
    // storing value for return or printing first then traverse further
    auto dfs_pre_order(Node* current_node) -> void {
        if (!current_node) return; // just in case tree is empty
        std::cout << current_node->value << " ";

        if (current_node->left) {
            dfs_pre_order(current_node->left);
        }
        if (current_node->right) {
            dfs_pre_order(current_node->right);
        }
    }

    // post order means do operations after all the travelsal
    auto dfs_post_order(Node* current_node) -> void {
        if (!current_node) return;

        if (current_node->left) {
            dfs_post_order(current_node->left);
        }
        if (current_node->right) {
            dfs_post_order(current_node->right);
        }

        std::cout << current_node->value << " ";
    }

    // in order operation after left (or first travelsal)
    // and this gives us sorted output from smallest to biggest element
    // because we were sorting them on instert
    auto dfs_in_order(Node* current_node) -> void {
        if (!current_node) return;

        if (current_node->left) {
            dfs_in_order(current_node->left);
        }

        std::cout << current_node->value << " ";

        if (current_node->right) {
            dfs_in_order(current_node->right);
        }
    }

public:

    auto r_contains(const Type& value) -> bool {
        return r_contains(m_root, value);
    }

    auto r_insert(const Type& value) -> void {
        if (!m_root) m_root = new Node{ value };
        r_insert(m_root, value);
    }

    auto r_delete(const Type& value) -> void {
        m_root = r_delete(m_root, value);
    }

    auto bfs() -> void {
        Queue<Node*, VecForQ> my_que;
        my_que.push(m_root);

        while (my_que.size() > 0) {
            Node* current_node{ my_que.front() };
            my_que.pop();

            std::cout << current_node->value << " ";

            if (current_node->left) {
                my_que.push(current_node->left);
            }
            if (current_node->right) {
                my_que.push(current_node->right);
            }
        }
    }

    auto dfs_pre_order() -> void { dfs_pre_order(m_root); }
    
    auto dfs_post_order() -> void { dfs_post_order(m_root); }

    auto dfs_in_order() -> void { dfs_in_order(m_root); }
};
#pragma endregion