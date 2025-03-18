module;

#include <iostream>
#include <string>

export module RedBlack_Tree;

import Queue;

namespace my_junk::internal
{
    #pragma region Node Implementation
    enum struct Color : uint8_t
    {
        RED = 0b0
        , BLACK = 0b1
    };

    template <typename Type>
    struct RedBlack_Node {
        Type value{};
        RedBlack_Node* parent{nullptr};
        RedBlack_Node* left{nullptr};
        RedBlack_Node* right{nullptr};
        Color color{Color::RED};

        RedBlack_Node() = default;
        explicit RedBlack_Node(const Type& value, RedBlack_Node* parent = nullptr)
         : value{value}, parent{parent}, left{nullptr}, right{nullptr} {};

        friend std::ostream& operator<<(std::ostream& os, const RedBlack_Node* node)
        {
            os << "[ address: 0x" << std::hex << reinterpret_cast<uintptr_t>(node)
            << " color: " << (node == nullptr ? "none" : (node->color == Color::RED ? "Red" : "Black"))
            << " value: ";
         
            if (node == nullptr) {
                os << "none";
            } else {
                os << std::dec << node->value; 
            }
            
            os << ", parent: 0x" << std::hex << (node == nullptr ? 0 : reinterpret_cast<uintptr_t>(node->parent))
                << ", left: 0x" << std::hex << (node == nullptr ? 0 : reinterpret_cast<uintptr_t>(node->left))
                << ", right: 0x" << std::hex << (node == nullptr ? 0 : reinterpret_cast<uintptr_t>(node->right))
                << " ]" << std::dec;
            return os;
        }
    };
    #pragma endregion // Node Implementation
}

export namespace my_junk
{
    #pragma region RedBlack Tree Implementation
    template <typename Type>
    class RedBlackTree {
        using Node = internal::RedBlack_Node<Type>;

        Node* m_root{nullptr};
        size_t m_size{};

        auto deleteSubtree(Node* node) -> void {
            if (!node) return;

            deleteSubtree(node->left);
            deleteSubtree(node->right);

            std::cout << "Deleting node with value: [ " << node->value << " ]\n";
            
            delete node;
            --m_size;
        }

    public:

        RedBlackTree() = default;
        explicit RedBlackTree(const Type& value) : m_root{ new Node(value) }, m_size{1}
        {
            m_root->color = internal::Color::BLACK;
        }

        ~RedBlackTree() {
            std::cout << "\033[1;33m[ Red Black Tree Destructor ]\033[0m\n";
            deleteSubtree(m_root);
            m_root = nullptr;
            std::cout << "[ Tree size: " << m_size << "]\n";
        }

        friend std::ostream& operator<<(std::ostream& os, const RedBlackTree& storage) {
            os << "Tree size: " << storage.m_size << "\n";
            os << "\nValue view: ";
            printValueDfsInOrder(os, storage.m_root);
            return os << "\n";
        }

        static void printValueDfsInOrder(std::ostream& os, Node* node) {
            if (!node) return;

            os << "(";

            if (node->left) printValueDfsInOrder(os, node->left);

            os << " " << node->value << " ";

            if (node->right) printValueDfsInOrder(os, node->right);

            os << ")";
        }

        bool empty() const { return m_size == 0; }
        size_t size() const { return m_size; }

        // rework for parent link
        auto insert(const Type& value) -> bool {
            Node* new_node{ new Node(value) };

            if (empty()) {
                m_root = new_node;
                new_node->color = internal::Color::BLACK;
                ++m_size;
                std::cout << new_node << '\n';
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
                        new_node->parent = current;
                        ++m_size;
                        std::cout << new_node << '\n';
                        return true;
                    }
                    current = current->left;
                } else {
                    if (!current->right) {
                        current->right = new_node;
                        new_node->parent = current;
                        ++m_size;
                        std::cout << new_node << '\n';
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

        auto left_rotate(Node* x) -> void {

        }

        auto r_contains(Node* current_node, const Type& value) -> bool {
            if (!current_node) return false;

            if (current_node->value == value) return true;
            
            if (value < current_node->value)
                return r_contains(current_node->left, value);
            else 
                return r_contains(current_node->right, value);
        }

        auto r_insert(Node* current_node, Node* parent, const Type& value) -> Node* {
            if (!current_node) return new Node(value, parent); // rework for parent node* needed
            
            if (value < current_node->value) {
                current_node->left = r_insert(current_node->left, current_node, value);
            } else if (value > current_node->value) {
                current_node->right = r_insert(current_node->right, current_node, value);
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
                if (!current_node->left && current_node->right) {
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

        auto dfs_pre_order(Node* current_node) -> void {
            if (!current_node) return;

            std::cout << current_node->value << ' ';

            if (current_node->left) dfs_pre_order(current_node->left);
            if (current_node->right) dfs_pre_order(current_node->right);
        }

        auto dfs_in_order(Node* current_node) -> void {
            if (!current_node) return;

            if (current_node->left) dfs_in_order(current_node->left);

            std::cout << current_node->value << ' ';

            if (current_node->right) dfs_in_order(current_node->right);
        }

        auto dfs_post_order(Node* current_node) -> void {
            if (!current_node) return;

            if (current_node->left) dfs_post_order(current_node->left);
            if (current_node->right) dfs_post_order(current_node->right);

            std::cout << current_node->value << ' ';
        }

    public:

        auto r_contains(const Type& value) -> bool {
            return r_contains(m_root, value);
        }

        auto r_insert(const Type& value) -> void {
            if (!m_root) m_root = new Node{ value };
            m_root->color = internal::Color::BLACK;
            r_insert(m_root, value);
        }

        auto r_delete(const Type& value) -> void {
            m_root = r_delete(m_root, value);
        }

        auto bfs() -> void {
            Queue<Node*, VecForQ> node_que;
            node_que.push(m_root);

            while(!node_que.empty()) {
                Node* current_node{ node_que.front() };
                node_que.pop();

                std::cout << current_node->value << ' ';

                if (current_node->left) node_que.push(current_node->left);
                if (current_node->right) node_que.push(current_node->right);
            }
        }

        auto dfs_pre_order() -> void { dfs_pre_order(m_root); }
        
        auto dfs_post_order() -> void { dfs_post_order(m_root); }

        auto dfs_in_order() -> void { dfs_in_order(m_root); }
    };
    #pragma endregion // RedBlack Tree Implementation
}