class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
        int count = 0;
        int dp = 0;
        int prev = -1;

        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] < left && i > 0) {
                count += dp;
            }
            if (nums[i] > right) {
                dp = 0;
                prev = i;
            }
            if (left <= nums[i] && nums[i] <= right) {
                dp = i - prev;
                count += dp;
            }
        }

        return count;
    }
};
