class Solution {
public:
    bool checkArray(vector<int>& nums, int k) {
        const int n = nums.size();
        int prefixSum = 0;

        for (int i = 0; i < n; ++i) {
            if (prefixSum > nums[i]) {
                return false;
            }
            nums[i] -= prefixSum;
            prefixSum += nums[i];
            if (i >= k - 1) {
                prefixSum -= nums[i - k + 1];
            }
        }

        return prefixSum == 0;
    }
};
