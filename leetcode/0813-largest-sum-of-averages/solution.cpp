class Solution {
public:
    double largestSumOfAverages(vector<int>& nums, int k) {
        const int n = nums.size();
        vector<vector<double>> dp(n + 1, vector<double>(k + 1, 0));
        vector<int> prefixSum(n + 1, 0);

        for (int i = 1; i <= n; ++i) {
            prefixSum[i] = prefixSum[i - 1] + nums[i - 1];
            dp[i][1] = static_cast<double>(prefixSum[i]) / i;
        }

        for (int j = 2; j <= k; ++j) {
            for (int i = j; i <= n; ++i) {
                for (int m = j - 1; m < i; ++m) {
                    dp[i][j] = max(dp[i][j], dp[m][j - 1] + static_cast<double>(prefixSum[i] - prefixSum[m]) / (i - m));
                }
            }
        }

        return dp[n][k];
    }
};
