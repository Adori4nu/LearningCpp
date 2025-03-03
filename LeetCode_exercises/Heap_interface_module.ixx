module;

#include "../Vector.hpp"

#include <ostream>

export module Heap;
#pragma region Heap impl
export namespace my_junk
{
    template <typename Type>
    class Heap
    {
        Vector<Type> m_heap{};

        auto left_child(size_t index) -> size_t { return 2 * index + 1; }
        auto right_child(size_t index) -> size_t { return 2 * index + 2; }
        auto parrent(size_t index) -> size_t { return (index - 1) / 2; }
        
        auto swap(size_t index_1, size_t index_2) -> void {
            Type temp{ m_heap[index_1] };
            m_heap[index_1] = m_heap[index_2];
            m_heap[index_2] = temp;
        }
        
        auto heapify_up(size_t index) -> void {
            while (index > 0 && m_heap[index] > m_heap[parrent(index)]) {
                swap(index, parrent(index));
                index = parrent(index);
            }
        }

        auto heapify_down(size_t index) -> void {
            size_t max_index{ index };
            
            while (true) {
                size_t left_index{ left_child(index) };
                size_t right_index{ right_child(index) };

                if (left_index < m_heap.size() && m_heap[left_index] > m_heap[max_index]) {
                    max_index = left_index;
                }

                if (right_index < m_heap.size() && m_heap[right_index] > m_heap[max_index]) {
                    max_index = right_index;
                }

                if (max_index != index) {
                    swap(index, max_index);
                    index = max_index;
                } else {
                    return;
                }
            }
            
        }
        
    public:
        
        // we store nodes from index 0 it's easier for indexing 
        // childs and parrents also for resize function of vector
        // but there are implementations that starts from index 1
        auto insert(const Type& value) -> void { // lvalue references
            m_heap.PushBack(value);
            size_t current{ m_heap.Size() - 1 }; // index of currently inserted value

            heapify_up(current);
        }

        auto insert(Type&& value) -> void { // rvalue references
            m_heap.PushBack(std::move(value));

            heapify_up(m_heap.Size() - 1);
        }
        
        template <typename... Args>
        auto emplace(Args&&... args) -> void {
            m_heap.EmplaceBack(std::forward<Args>(args)...);
            heapify_up(size() - 1);
        }

        auto remove() -> Type {
            if (m_heap.empty()) {
                return Type{};
            }

            Type return_value{ m_heap.front() };

            if (m_heap.size() == 1) {
                m_heap.PopBack();
            } else {
                m_heap[0] = m_heap.back();
                m_heap.PopBack();
                heapify_down(0);
            }

            return return_value;
        }

        auto size() const -> const size_t { return m_heap.Size(); }
        auto operator[](size_t index) const -> const Type& { return m_heap[index]; }

        template <typename T>
        friend std::ostream& operator<<(std::ostream& os, const my_junk::Heap<T>& heap);
    };
#pragma endregion
#pragma region helper functions
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const my_junk::Heap<T>& heap)
    {
        if (heap.size() == 0) {
            return os << "[Empty Heap]\n";
        }

        size_t height{ 0 };
        size_t nodes{ 1 };
        while (nodes <= heap.size()) {
            ++height;
            nodes *= 2;
        }

        os << "\t[Max Heap]\n";

        size_t level{ 0 };
        size_t level_nodes{ 1 };
        size_t index{ 0 };

        while (level < height && index < heap.size()) {
            size_t spacing{ size_t((1 << (height - level - 1)) - 1) };

            for (size_t i{ 0 }; i < level_nodes && index < heap.size(); ++i) {
                for (size_t j{ 0 }; j < spacing; ++j) {
                    os << " ";
                }

                os << heap[index++];

                for (size_t j{ 0 }; j < spacing; ++j) {
                    os << " ";
                }

                if (i < level_nodes - 1) {
                    os << " ";
                }
            }

            os << "\n";

            ++level;
            level_nodes *= 2;
        }

        os << "\n[ Vector representation ]\n[";
        for (size_t i{ 0 }; i < heap.size(); ++i) {
            os << heap[i];
            if (i < heap.size() - 1) os << ", ";
        }
        os << "]\n";

        os << "\n[ Node relationships ]\n";
        for (size_t i{ 0 }; i < heap.size(); ++i) {
            os << "Node " << i << " (" << heap[i] << "): ";

            if (i > 0) {
                size_t parent_idx{ (i - 1) / 2 };
                os << "Parent = " << parent_idx << " (" << heap[parent_idx] << ") ";
            } else {
                os << "Root ";
            }

            size_t left_idx{ 2 * i + 1};
            if (left_idx < heap.size()) {
                os << "Left = " << left_idx << " (" << heap[left_idx] << ") ";
            }

            size_t right_idx{ 2 * i + 2};
            if (right_idx < heap.size()) {
                os << "Right = " << right_idx << " (" << heap[right_idx] << ") ";
            }

            os << "\n";
        }

        return os;
    }
};
#pragma endregion