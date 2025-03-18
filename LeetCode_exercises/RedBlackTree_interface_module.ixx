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

            os << " " << "(" << (node->color == internal::Color::RED ? "R" : "B") << ")"<< node->value << " ";

            if (node->right) printValueDfsInOrder(os, node->right);

            os << ")";
        }

        bool empty() const { return m_size == 0; }
        size_t size() const { return m_size; }

    private:

        auto transplant(Node* u, Node* v) -> void {
            if (!u->parent) {
                m_root = v;
            } else if (u == u->parent->left) {
                u->parent->left = v;
            } else {
                u->parent->right = v;
            }

            if (v) {
                v->parent = u->parent;
            }
        }

        auto left_rotate(Node* x) -> void {
            Node* y{ x->right };                // Get right child
            x->right = y->left;                 // Move y's left subtree to x's right

            if (y->left) y->left->parent = x;

            y->parent = x->parent;              // Connect y to x's parent

            // Connect x to y's parent
            if (!x->parent) m_root = y;         // y becomes the new root
            else if ( x == x->parent->left)
                x->parent->left = y;            // y becomes left child
            else
                x->parent->right = y;           // y becomes right child

            y->left = x;                        // Make x the left child of y
            x->parent = y;                      // Update x's parent
        }

        auto right_rotate(Node* y) -> void {
            Node* x{ y->left };          // Get left child
            y->left = x->right;         // Move x's right subtree to y's left
            
            if (x->right)
                x->right->parent = y;
                
            x->parent = y->parent;      // Connect x to y's parent
            
            // Connect y's parent to x
            if (!y->parent) m_root = x;             // x becomes the new root
            else if (y == y->parent->right)
                y->parent->right = x;   // x becomes right child
            else
                y->parent->left = x;    // x becomes left child
                
            x->right = y;               // Make y the right child of x
            y->parent = x;              // Update y's parent
        }

        auto insert_fixup(Node* z) -> void {
            using enum internal::Color;
            while (z->parent && z->parent->color == RED) {
                if (z->parent == z->parent->parent->left) {
                    Node* y{ z->parent->parent->right }; // Uncle

                    // Case 1: Uncle is red
                    if (y && y->color == RED) {
                        z->parent->color = BLACK;
                        y->color = BLACK;
                        z->parent->parent->color = RED;
                        z = z->parent->parent;
                    } else {
                        // Case 2: Uncle is black, z is a right child (triangle)
                        if (z == z->parent->right) {
                            z = z->parent;
                            left_rotate(z);
                        }

                        // Case 3: Uncle is black, z is a left child (line)
                        z->parent->color = BLACK;
                        z->parent->parent->color = RED;
                        right_rotate(z->parent->parent);
                    }
                } else {
                    Node* y{ z->parent->parent->left };

                    // Case 1: Uncle is Red
                    if (y && y->color == RED) {
                        z->parent->color = BLACK;
                        y->color = BLACK;
                        z->parent->parent->color = RED;
                        z = z->parent->parent;
                    } else {
                        // Case 2: Uncle is black z is a left child (triangle)
                        if (z == z->parent->left) {
                            z = z->parent;
                            right_rotate(z);
                        }

                        // Case 3: Uncle is black, z is a right child (line)
                        z->parent->color = BLACK;
                        z->parent->parent->color = RED;
                        left_rotate(z->parent->parent);
                    }
                }
            }

            m_root->color = BLACK;
        }

        auto delete_fixup(Node* x, Node* x_parent, bool is_left_child) {
            using enum internal::Color;
            // Continue until x is the root or x is red
            // (if x is red, we can simply recolor it black)
            while ((!x || x->color == BLACK) && x != m_root) {
                if (!x) {
                    // Handle cases where x is nullptr (treated as a "doubly black" nullptr node)
                    if (is_left_child) {
                        // Node is left child
                        Node* w{ x_parent->right };

                        // Case 1: Sibling is red
                        if (w && w->color == RED) {
                            w->color = BLACK;
                            x_parent->color = RED;
                            left_rotate(x_parent);
                            w = x_parent->right;
                        }

                        // Case 2: Sibling is black with two black children
                        if ((!w->left || w->left->color == BLACK) &&
                            (!w->right || w->right->color == BLACK)) {
                            w->color = RED;
                            x = x_parent;
                            if (x->parent) {
                                is_left_child = (x == x->parent->left);
                                x_parent = x->parent;
                            } else {
                                is_left_child = false;
                            }
                        } else {
                            // Case 3: Sibling is black with red left child and black right child
                            if (!w->right || w->right->color == BLACK) {
                                if (w->left) w->left->color = BLACK;
                                w->color = RED;
                                right_rotate(w);
                                w = x_parent->right;
                            }

                            // Case 4: Sibling is black with red right child
                            w->color = x_parent->color;
                            x_parent->color = BLACK;
                            if (w->right) w->right->color = BLACK;
                            left_rotate(x_parent);
                            x = m_root;
                        }
                    } else {
                        // Node is right child - mirror cases
                        Node* w{ x_parent->left }; // Sibling of x

                        // Case 1: Sibling is red
                        if (w && w->color == RED) {
                            w->color = BLACK;
                            x_parent->color = RED;
                            right_rotate(x_parent);
                            w = x_parent->left;
                        }

                        // Case 2: Sibling is black with two black children
                        if ((!w->right || w->right->color == BLACK) &&
                            (!w->left || w->left->color == BLACK)) {
                            w->color = RED;
                            x = x_parent;
                            if (x->parent) {
                                is_left_child = (x == x->parent->left);
                                x_parent = x->parent;
                            } else {
                                // x is the new root
                                is_left_child = false;
                            }
                        } else {
                            // Case 3: Sibling is black with red right child and black left child
                            if (!w->left || w->left->color == BLACK) {
                                if (w->right) w->right->color = BLACK;       // Recolor right child
                                w->color = RED;                              // Recolor sibling
                                leftRotate(w);                               // Rotate sibling
                                w = x_parent->left;                          // Update sibling
                            }

                            // Case 4: Sibling is black with red left child
                            w->color = x_parent->color;         // Copy parent's color
                            x_parent->color = BLACK;            // Recolor parent
                            if (w->left) w->left->color = BLACK; // Recolor left child
                            rightRotate(x_parent);              // Rotate parent
                            x = m_root;                         // Finish by moving to root
                        }
                    }
                } else {
                    // Hadle cases where x is not nullptr
                    if (x == x->parent->left) {
                        Node* w{ x->parent->right }; // Sibling of x

                        // Case 1: Sibling is red
                        if (w && w->color == RED) {
                            w->color = BLACK;
                            x->parent->color = RED;
                            left_rotate(x->parent);
                            w = x->parent->right;
                        }
                        
                        // Case 2: Sibling is black with two black children
                        if ((!w->left || w->left->color == BLACK) && 
                            (!w->right || w->right->color == BLACK)) {
                            w->color = RED;
                            x = x->parent;
                        } else {
                            // Case 3: Sibling is black with red left child and black right child
                            if (!w->right || w->right->color == BLACK) {
                                if (w->left) w->left->color = BLACK;
                                w->color = RED;
                                right_rotate(w);
                                w = x->parent->right;
                            }
                            
                            // Case 4: Sibling is black with red right child
                            w->color = x->parent->color;
                            x->parent->color = BLACK;
                            if (w->right) w->right->color = BLACK;
                            left_rotate(x->parent);
                            x = m_root;
                        }
                    } else {
                        // Mirror cases for right child
                        Node* w = x->parent->left; // Sibling of x
                        
                        // Case 1: Sibling is red
                        if (w && w->color == RED) {
                            w->color = BLACK;
                            x->parent->color = RED;
                            rightRotate(x->parent);
                            w = x->parent->left;
                        }
                        
                        // Case 2: Sibling is black with two black children
                        if ((!w->right || w->right->color == BLACK) && 
                            (!w->left || w->left->color == BLACK)) {
                            w->color = RED;
                            x = x->parent;
                        } else {
                            // Case 3: Sibling is black with red right child and black left child
                            if (!w->left || w->left->color == BLACK) {
                                if (w->right) w->right->color = BLACK;
                                w->color = RED;
                                leftRotate(w);
                                w = x->parent->left;
                            }
                            
                            // Case 4: Sibling is black with red left child
                            w->color = x->parent->color;
                            x->parent->color = BLACK;
                            if (w->left) w->left->color = BLACK;
                            rightRotate(x->parent);
                            x = m_root;
                        }
                    }
                }
            }

            if (x) x->color = BLACK;
        }

    public:

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
                        insert_fixup(new_node);
                        std::cout << new_node << '\n';
                        return true;
                    }
                    current = current->left;
                } else {
                    if (!current->right) {
                        current->right = new_node;
                        new_node->parent = current;
                        ++m_size;
                        insert_fixup(new_node);
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
        
        auto find(const Type& value) -> Node* {
            Node* current{ m_root };
            while (current) {
                if (value == current->value) return &current; 

                if (value < current->value) current = current->left;
                else current = current->right;
            }
            return nullptr;
        }

        auto delete_node(const Type& value) -> void {
            using enum internal::Color;
            // Find the node to delete
            Node* z{ find(value) };
            if (!z) return; // Node not found
            
            // Track original color for fixup later
            internal::Color original_color = z->color;
            Node* x = nullptr;       // Replacement node
            Node* x_parent = nullptr; // Parent of replacement node
            bool is_left_child = false;

            // Case 1: Node has no left child
            if (!z->left) {
                x = z->right;
                // Transplant z with its right child (which might be nullptr)
                transplant(z, z->right);
                if (x) x_parent = x->parent;
                else x_parent = z->parent;
                is_left_child = (x_parent && x_parent->left == x);
            }
            // Case 2: Node has no right child
            else if (z->right == nullptr) {
                x = z->left;
                // Transplant z with its left child
                transplant(z, z->left);
                if (x) x_parent = x->parent;
                else x_parent = z->parent;
                is_left_child = (x_parent && x_parent->left == x);
            }
            // Case 3: Node has both children
            else {
                // Find successor (minimum in right subtree)
                Node* y{ min_val(z->right)};
                original_color = y->color;
                x = y->right;
                
                if (y->parent == z) {
                    // y is z's direct right child
                    if (x) x->parent = y;
                    x_parent = y;
                    is_left_child = false; // x is a right child
                } else {
                    // y is deeper in the right subtree
                    x_parent = y->parent;
                    is_left_child = (y == y->parent->left);
                    
                    // Transplant y with its right child
                    transplant(y, y->right);
                    
                    // Link y into z's position
                    y->right = z->right;
                    y->right->parent = y;
                }
                
                // Replace z with y
                transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }

            delete z;
            --m_size;

            // If we deleted a BLACK node, we need to fix the tree
            if (original_color == BLACK) {
                deleteFixup(x, x_parent, is_left_child);
            }
        }

    private:

        auto r_contains(Node* current_node, const Type& value) -> bool {
            if (!current_node) return false;

            if (current_node->value == value) return true;
            
            if (value < current_node->value)
                return r_contains(current_node->left, value);
            else 
                return r_contains(current_node->right, value);
        }

        // need fix for recoloring
        // auto r_insert(Node* current_node, Node* parent, const Type& value) -> Node* {
        //     if (!current_node) return new Node(value, parent);
            
        //     if (value < current_node->value) {
        //         current_node->left = r_insert(current_node->left, current_node, value);
        //     } else if (value > current_node->value) {
        //         current_node->right = r_insert(current_node->right, current_node, value);
        //     }

        //     return current_node;
        // }

        auto min_val(Node* current_node) -> Type {
            while (current_node->left) {
                current_node = current_node->left;
            }
            return current_node->value;
        }

        // auto r_delete(Node* current_node, const Type& value) -> Node* {
        //     if (!current_node) return nullptr;

        //     if (value < current_node->value) {
        //         current_node->left = r_delete(current_node->left, value);
        //     } else if (value > current_node->value) {
        //         current_node->right = r_delete(current_node->right, value);
        //     } else {
        //         if (!current_node->left && current_node->right) {
        //             delete current_node;
        //             return nullptr;
        //         } else if (!current_node->left) {
        //             Node* temp{ current_node->right };
        //             delete current_node;
        //             --m_size;
        //             return temp;
        //         } else if (!current_node->right) {
        //             Node* temp{ current_node->left };
        //             delete current_node;
        //             --m_size;
        //             return temp;
        //         } else {
        //             Type sub_tree_min{ min_val(current_node->right) };
        //             current_node->value = sub_tree_min;
        //             current_node->right = r_delete(current_node->right, sub_tree_min);
        //         }
        //     }

        //     return current_node;
        // }

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

        // recoloring fix needed
        // auto r_insert(const Type& value) -> void {
        //     if (!m_root) m_root = new Node{ value };
        //     m_root->color = internal::Color::BLACK;
        //     r_insert(m_root, nullptr, value);
        // }

        // need fix same
        // auto r_delete(const Type& value) -> void {
        //     m_root = r_delete(m_root, value);
        // }

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