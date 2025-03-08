module;

#include <utility>
#include "../Vector.hpp"

export module Sorts;

export namespace my_junk
{
    #pragma region Bubble Sort
    template <typename T>
    auto bubble_sort(Vector<T>& container) -> void {
        for (size_t i{container.Size() - 1}; i > 0; --i) {
            for (size_t j{0}; j < i; ++j) {
                if (container[j] > container[j+1]) {
                    T temp = std::move(container[j]);
                    container[j] = std::move(container[j+1]);
                    container[j+1] = std::move(temp);
                    // std::swap(container[j], container[j+1]); // or
                }
            }
        }
    }
    #pragma endregion
    #pragma region Selection Sort
    template <typename T>
    auto selection_sort(Vector<T>& container) -> void {
        for (size_t i{0}; i < container.Size() - 1; ++i) {
            size_t min_index{i};
            for (size_t j{i+1}; j < container.Size(); ++j) {
                if (container[j] < container[min_index]) {
                    min_index = j;
                }
            }
            if (min_index != i) {
                T temp{ std::move(container[i]) };
                container[i] = std::move(container[min_index]);
                container[min_index] = std::move(temp);
            }
        }
    }
    #pragma endregion
    #pragma region Insertion Sort
    template <typename T>
    auto insertion_sort(Vector<T>& container) -> void {
        for (size_t i{1}; i < container.Size(); ++i) {
            // picking up the key
            T key{ std::move(container[i]) };
            size_t j{i};

            // overriding element with the value of preivous one
            // if its bigger than current key val
            // j > 0 must be the begining condition
            while (j > 0 && container[j - 1] > key) {
                container[j] = std::move(container[j - 1]);
                --j;
            }

            // storing the key at proper index for it
            container[j] = std::move(key);
        }
    }
    #pragma endregion
} // namespace my_junk
