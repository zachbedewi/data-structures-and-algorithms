class Solution {
public:
    bool splitArraySameAverage(vector<int>& nums) {
        const int n = nums.size();
        int totalSum = ranges::fold_left(nums, 0, plus<int>());

        vector<int> dp(totalSum + 1, 0);
        dp[0] = 1;

        for (const auto num : nums) {
            for (int sum = totalSum; sum >= num; --sum) {
                dp[sum] |= dp[sum - num] << 1;
            }
        }

        for (int k = 1; k <= n / 2; ++k) {
            if (k * totalSum % n == 0 && (dp[k * totalSum / n] & 1 << k) != 0) {
                return true;
            }
        }

        return false;
    }
};
