int maxSubarraySum(vector<int>& nums) {
    int n = nums.size();
    int sum = nums[0];
    int maxi = nums[0];
    for (int i = 1; i < n; i++) {
        sum = max(nums[i], sum + nums[i]);  // extend or restart
        maxi = max(maxi, sum);              // track best
    }
    return maxi;
}

int minSubarraySum(vector<int>& nums) {
    int n = nums.size();
    int sum = nums[0];
    int mini = nums[0];
    for (int i = 1; i < n; i++) {
        sum = min(nums[i], sum + nums[i]);  // extend or restart
        mini = min(mini, sum);              // track worst
    }
    return mini;
}
