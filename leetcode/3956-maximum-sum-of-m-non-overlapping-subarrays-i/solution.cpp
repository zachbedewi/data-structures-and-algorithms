class Solution {
  public:
    long long maximumSum(vector<int> &nums, int m, int l, int r) {
        const auto n = nums.size();
        auto prefix = vector<long long>(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        auto dp = vector(m + 1, vector<long long>(n + 1, -4e18));
        for (int i = 0; i <= n; ++i) {
            dp[0][i] = 0;
        }

        long long res = numeric_limits<long long>::min();
        for (int k = 1; k <= m; ++k) {
            deque<int> dq;
            for (int i = 1; i <= n; ++i) {
                dp[k][i] = dp[k][i - 1];
                if (i - l >= 0) {
                    const auto curr = dp[k - 1][i - l] - prefix[i - l];
                    while (!dq.empty() &&
                           dp[k - 1][dq.back()] - prefix[dq.back()] < curr) {
                        dq.pop_back();
                    }
                    dq.push_back(i - l);
                }

                while (!dq.empty() && dq.front() < i - r) {
                    dq.pop_front();
                }

                if (!dq.empty()) {
                    dp[k][i] = max(dp[k][i], dp[k - 1][dq.front()] + prefix[i] -
                                                 prefix[dq.front()]);
                }
            }
            res = max(res, dp[k][n]);
        }

        return res;
    }
};
