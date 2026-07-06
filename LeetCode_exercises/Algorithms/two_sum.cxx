#include <vector>
#include <unordered_map>

auto two_sum(const std::vector<int>& nums, int target) -> std::vector<int> {
    std::unordered_map<int, int> num_to_index;

    for (size_t i{0}; i < nums.size(); ++i) {
        int complement{ target - nums[i] };

        if (num_to_index.find(complement) != num_to_index.end()) {
            return { num_to_index[complement], static_cast<int>(i) };
        }

        num_to_index[nums[i]] = static_cast<int>(i);
    }

    return {};
}