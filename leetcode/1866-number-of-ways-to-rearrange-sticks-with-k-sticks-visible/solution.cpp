class Solution {
  public:
    int rearrangeSticks(int n, int k) {
        auto dp = vector(n + 1, vector<long long>(k + 1, 0));
        dp[0][0] = 1;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= k; ++j) {
                dp[i][j] =
                    (((i - 1) * dp[i - 1][j] % MOD) + dp[i - 1][j - 1]) % MOD;
            }
        }

        return dp[n][k];
    }

  private:
    static constexpr int MOD = 1e9 + 7;
};
