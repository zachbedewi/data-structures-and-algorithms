class Solution {
public:
    int stoneGameVII(vector<int>& stones) {
        const int n = stones.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        vector<int> prefixSum(n + 1, 0);
        inclusive_scan(stones.begin(), stones.end(), prefixSum.begin() + 1);

        for (const auto i : views::iota(0, n - 1) | views::reverse) {
            for (const auto j : views::iota(i + 1, n)) {
                const auto withoutI = prefixSum[j + 1] - prefixSum[i + 1];
                const auto withoutJ = prefixSum[j] - prefixSum[i];
                dp[i][j] = max(withoutI - dp[i + 1][j], withoutJ - dp[i][j - 1]);
            }
        }

        return dp[0][n - 1];
    }
};
