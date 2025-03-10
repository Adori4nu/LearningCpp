module;

#include <utility>
#include <print>
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
    // n^2 generaly but when data is sorted it is O(n)
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
}
namespace my_junk::details
{
    #pragma region Merge Impl
    template <typename T>
    auto merge(Vector<T>& container
            , typename Vector<T>::Iterator begin
            , typename Vector<T>::Iterator mid
            , typename Vector<T>::Iterator end) -> void {
        
            size_t left_size{ size_t(mid - begin) };
            size_t right_size{ size_t(end - mid) };

            Vector<T> left_subvec;
            Vector<T> right_subvec;

            auto it{ begin };
            for (size_t i{0}; i < left_size; ++i) {
                left_subvec.PushBack(*it);
                ++it;
            }

            for (size_t i {0}; i < right_size; ++i) {
                right_subvec.PushBack(*it);
                ++it;
            }

            size_t left_index{0};
            size_t right_index{0};
            it = begin;

            while (left_index < left_size && right_index < right_size) {
                if (left_subvec[left_index] <= right_subvec[right_index]) {
                    *it = std::move(left_subvec[left_index]);
                    ++left_index;
                } else {
                    *it = std::move(right_subvec[right_index]);
                    ++right_index;
                }
                ++it;
            }

            while (left_index < left_size) {
                *it = std::move(left_subvec[left_index]);
                ++left_index;
                ++it;
            }

            while (right_index < right_size) {
                *it = std::move(right_subvec[right_index]);
                ++right_index;
                ++it;
            }
    }

    // cuts the vector in halves until it gets to
    // 1 element sub vectors then it exit's recursive
    // merge_sort_impls and percide to merge function
    // that is reinserting elements from lowest to higest
    // to 2 element sub vectors then again exits and
    // reinserts in order to biger vec
    // until it mergese everything back
    template <typename T>
    auto merge_sort_impl(Vector<T>& container
                , typename Vector<T>::Iterator begin
                , typename Vector<T>::Iterator end) -> void {
        
        if (end - begin <= 1) {
            return;
        }

        auto mid{ begin + (end - begin) / 2 };

        merge_sort_impl(container, begin, mid);
        merge_sort_impl(container, mid, end);

        merge(container, begin, mid, end);
    }
    #pragma endregion
} // namespace my_junk::details
export namespace my_junk
{
    #pragma region Merge Sort
    template <typename T>
    auto merge_sort(Vector<T>& container) -> void {
        details::merge_sort_impl(container, container.begin(), container.end());
    }
    #pragma endregion
} // namespace my_junk
namespace my_junk::details
{
    #pragma region Pivot and Swap
    template <typename T>
    auto swap(T& first, T& second) -> void {
        T temp{ std::move(first) };
        first = std::move(second);
        second = std::move(temp);
    }

    template <typename T>
    auto partition(Vector<T>& container, typename Vector<T>::Iterator start, 
        typename Vector<T>::Iterator end) -> typename Vector<T>::Iterator {
        T pivot_value{ *start };
        auto swap_pos = start;
        // iterate through all elements except the pivot one
        for (auto current{ start + 1 }; current <= end; ++current) {
            if (*current < pivot_value) {
                ++swap_pos;
                if (swap_pos != current) {
                    std::println("Swapping: {} with {}", *swap_pos, *current);
                    swap(*swap_pos, *current);
                }
            }
        }
        if (start != swap_pos) {
            std::println("Swapping: pivot {} with {}", *start, *swap_pos);
            swap(*start, *swap_pos);
        }

        return swap_pos;
    }

    template <typename T>
    auto quick_sort_impl(Vector<T>& container, typename Vector<T>::Iterator start
            , typename Vector<T>::Iterator end) -> void {
        if ((end - start) < 1) return;
        
        auto pivot_position{ partition(container, start, end) };

        // Sort elements before and after pivot
        quick_sort_impl(container, start, pivot_position - 1);
        quick_sort_impl(container, pivot_position + 1, end);
    }
    #pragma endregion
} // namespace my_junk::details

export namespace my_junk
{
    #pragma region Quick Sort
    template <typename T>
    auto quick_sort(Vector<T>& container) -> void {
        if (container.Size() <= 1) {
            return;
        }

        details::quick_sort_impl(container, container.begin(), container.end() - 1);
    }
    #pragma endregion
} // namespace my_junk
