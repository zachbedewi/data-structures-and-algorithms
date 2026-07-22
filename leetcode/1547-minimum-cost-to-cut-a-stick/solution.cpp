class Solution {
  public:
    int minCost(int n, vector<int> &cuts) {
        cuts.push_back(0);
        cuts.push_back(n);
        ranges::sort(cuts);

        auto m = cuts.size();

        vector<vector<int>> dp(m, vector<int>(m, 0));

        for (auto len{2}; len < m; ++len) {
            for (auto i{0}; i < m - len; ++i) {
                auto j{i + len};
                dp[i][j] = numeric_limits<int>::max();
                for (auto k{i + 1}; k < j; ++k) {
                    dp[i][j] =
                        min(dp[i][j], dp[i][k] + dp[k][j] + cuts[j] - cuts[i]);
                }
            }
        }

        return dp[0][m - 1];
    }
};
