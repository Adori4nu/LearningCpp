#include <iostream>

int binary_search_gf(int heystack[], int size_of_heystack, int needle)
{
    int low = 0;
    int high = size_of_heystack;

    while( low <= high)
    {
        int mid = low + (high - low) / 2;

        if (heystack[mid] == needle)
            return mid;
        else if (heystack[mid] < needle)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
};

int binary_search_fm(int heystack[], int size_of_heystack, int needle)
{
    int low = 0;
    int high = size_of_heystack;

    do {
        const int mid = low + (high - low) / 2;
        const int value = heystack[mid];

        if (value == needle) {
            return mid;
        } else if (value > needle) {
            high = mid;
        } else {
            low = mid + 1;
        }
    } while (low < high);

    return -1;
};

int main() {
    int heystack[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int needle = 5;
    int size_of_heystack = sizeof(heystack) / sizeof(heystack[0]);
    int size_of_heystack_2 = *(&heystack + 1) - heystack;
    int index = binary_search_gf(heystack, size_of_heystack, needle);
    int index_2 = binary_search_fm(heystack, size_of_heystack, 7);
    std::cout << size_of_heystack << " index: " << index << std::endl;
    std::cout << size_of_heystack_2 << " index_2: " << index_2 << std::endl;
    int array[5];
   
    std::cout << "array = " << array << " : &array = " << &array;
    std::cout << "array + 1 = " << array + 1 << " : &array + 1 = " << &array + 1;
}