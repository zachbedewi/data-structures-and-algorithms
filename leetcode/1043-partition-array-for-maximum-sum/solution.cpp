class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        const int n = arr.size();
        vector<int> dp(n + 1, 0);

        for (int i = 1; i <= n; ++i) {
            int partitionMax = arr[i - 1];
            for (int j = 1; j <= k && i - j >= 0; ++j) {
                partitionMax = max(partitionMax, arr[i - j]);
                dp[i] = max(dp[i], dp[i - j] + partitionMax * j);
            }
        }

        return dp[n];
    }
};
