class Solution {
  public:
    int minOperations(vector<int> &nums, int k) {
        const auto n = nums.size();
        if (k > n / 2)
            return -1;
        if (k == 0)
            return 0;
        if (n == 2)
            return nums[0] == nums[1] ? 1 : 0;

        auto cost{vector<int>(n, 0)};
        for (int i = 0; i < n; ++i) {
            const auto left = nums[(i - 1 + n) % n];
            const auto right = nums[(i + 1) % n];
            cost[i] = max(0, max(left, right) + 1 - nums[i]);
        }

        long long res = numeric_limits<int>::max();
        res = min(res, solve(cost, 1, n - 1, n, k));
        if (k >= 1) {
            res = min(res, cost[0] + solve(cost, 2, n - 2, n, k - 1));
        }

        return res == numeric_limits<int>::max() ? -1 : res;
    }

  private:
    long long solve(const vector<int> &cost, int start, int end, int n, int k) {
        auto dp{vector(n + 2,
                       vector<long long>(k + 1, numeric_limits<int>::max()))};
        dp[start][0] = 0;

        for (int i = start; i <= end; ++i) {
            for (int j = 0; j <= k; ++j) {
                if (dp[i][j] == numeric_limits<int>::max())
                    continue;

                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);

                if (j + 1 <= k) {
                    dp[i + 2][j + 1] =
                        min(dp[i + 2][j + 1], dp[i][j] + cost[i]);
                }
            }
        }

        return min(dp[end + 1][k], dp[end + 2][k]);
    }
};
