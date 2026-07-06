bool canJump(vector<int>& nums) {
    int goal_post{ static_cast<int>(nums.size()) };

    for (int i{ static_cast<int>(nums.size()) - 1}; i >= 0; --i) {
        if (i + nums[i] >= goal_post) goal_post = i;
    }

    return goal_post == 0;
}