class Solution {
public:
    int countOfPairs(vector<int>& nums) {
        const int n = nums.size();
        const int m = ranges::max(nums);
        vector<int> dp(m + 1);
        vector<int> prefix(m + 2);

        for (int v = 0; v <= nums[0]; v++) {
            ++dp[v];
        }

        for (int i = 1; i < n; i++) {
            const int d = max(0, nums[i] - nums[i - 1]);
            for (int v = 0; v <= m; v++) {
                prefix[v + 1] = (prefix[v] + dp[v]) % kMod;
            }

            fill(dp.begin(), dp.end(), 0);
            for (int v = 0; v <= nums[i]; v++) {
                int hi = v - d;
                if (hi >= 0) {
                    dp[v] = prefix[hi + 1] % kMod;
                }
            }
        }

        int res = 0;
        for (int v = 0; v <= nums[n - 1]; v++) {
            res = (res + dp[v]) % kMod;
        }
        return res;
    }

private:
    static constexpr int kMod = 1'000'000'007;
};
