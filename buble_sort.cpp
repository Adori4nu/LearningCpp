#include <iostream>

void buble_sort(int* unsorted_array, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (unsorted_array[j] > unsorted_array[j+1])
            {
                // int tmp = unsorted_array[j];
                // unsorted_array[j] = unsorted_array[j+1];
                // unsorted_array[j+1] = tmp;

                unsorted_array[j] ^= unsorted_array[j+1];
                unsorted_array[j+1] ^= unsorted_array[j];
                unsorted_array[j] ^= unsorted_array[j+1];
            }
        }
    }
}

int main() {
    int heystack[] = {1, 5, 3, 6, 4, 9, 7, 8, 2};
    int size_of_heystack = sizeof(heystack) / sizeof(heystack[0]);
    buble_sort(heystack, size_of_heystack);
    for (const auto& val : heystack)
    {
        std::cout << val << " ";
    }
}