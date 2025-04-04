#include <iostream>
#include <unordered_map>

int countPairs_r(int arr[], int size, int i, int j) {
    if (i >= size - 1) return 0; // in case we have only 0 or 1 element
    
    if (j >= size) return countPairs_r(arr, size, i + 1, i + 2);

    int count{0};
    if (arr[i] - i == arr[j] - (j)) {
        count = 1;
    }

    return count + countPairs_r(arr, size, i, j + 1);
}

int countConsecutivePairs_r(int arr[], int size) {
    if (size < 2) return 0;

    return countPairs_r(arr, size, 0, 1);
}

int countConsecutivePairsBruteForce(int arr[], int size) {
    int count = 0;
    
    // Check all consecutive pairs
    for (int i = 0; i < size - 1; i++) {
        for (int j{i+1}; j < size; ++j) {
            if ( arr[i] - i == arr[j] - j) {
                count++;
            }
        }
    }
    
    return count;
}

// Recursive helper function to count occurrences of each value a[i] - i
void countDifferencesRecursive(int arr[], int size, int index, std::unordered_map<int, int>& diffCount) {
    // Base case: We've processed the entire array
    if (index >= size) {
        return;
    }
    
    // Calculate a[i] - i for the current element
    int diff = arr[index] - index;
    
    // Increment the count for this difference value
    diffCount[diff]++;
    
    // Process the next element recursively
    countDifferencesRecursive(arr, size, index + 1, diffCount);
}

// Function to calculate pairs from frequency counts
int calculatePairsFromCounts(const std::unordered_map<int, int>& diffCount) {
    int totalPairs = 0;
    
    // For each unique difference value, calculate the number of pairs
    for (const auto& entry : diffCount) {
        int count = entry.second;
        
        // Number of pairs is n*(n-1)/2 where n is the frequency
        totalPairs += (count * (count - 1)) / 2;
    }
    
    return totalPairs;
}

// Wrapper function
int countPairsOptimized(int arr[], int size) {
    if (size < 2) {
        return 0;
    }
    
    std::unordered_map<int, int> diffCount;
    
    // Recursively count occurrences of a[i] - i
    countDifferencesRecursive(arr, size, 0, diffCount);
    
    // Calculate pairs from frequency counts
    return calculatePairsFromCounts(diffCount);
}

auto main() -> int {
    int arr1[]{1,2,3};
    int size1{sizeof arr1 / sizeof arr1[0]};

    std::cout << "\033[1;36m[Example 1]\n{1,2,3}\033[0m\n";
    std::cout << "Recursive: ";
    std::cout << countConsecutivePairs_r(arr1, size1);
    std::cout << "\nBrute Force: " << countConsecutivePairsBruteForce(arr1, size1);
    std::cout << "\nMap Optimized Recursion O(n): " << countPairsOptimized(arr1, size1);
    
    std::cout << "\n\033[1;35m[Example 2]\n{3,4,9,10}\033[0m\n";
    
    int arr2[]{3,4,9,10};
    int size2{sizeof arr2 / sizeof arr2[0]};
    
    std::cout << "Recursive: ";
    std::cout << countConsecutivePairs_r(arr2, size2);
    std::cout << "\nBrute Force: " << countConsecutivePairsBruteForce(arr2, size2);
    std::cout << "\nMap Optimized Recursion O(n): " << countPairsOptimized(arr2, size2);
}