module;

#include <utility>
#include "../Vector.hpp"

export module Sorts;

export namespace my_junk
{
    #pragma region Buble Sort
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
} // namespace my_junk
