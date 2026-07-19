class Solution {
  public:
    int minScoreTriangulation(vector<int> &values) {
        auto const n = values.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 2; j <= n - 1; ++j) {
                dp[i][j] = numeric_limits<int>::max();
                for (int k = i + 1; k < j; ++k) {
                    dp[i][j] =
                        min(dp[i][j], dp[i][k] + dp[k][j] +
                                          values[i] * values[j] * values[k]);
                }
            }
        }

        return dp[0][n - 1];
    }
};
