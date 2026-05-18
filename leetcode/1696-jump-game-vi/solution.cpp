class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        const int n = nums.size();
        vector<int> dp(n, 0);
        dp[0] = nums[0];

        deque<int> monoQ {{0}};

        for (const auto i : views::iota(1, n)) {
            while (i - monoQ.front() > k) {
                monoQ.pop_front();
            }

            dp[i] = nums[i] + dp[monoQ.front()];

            while (!monoQ.empty() && dp[i] > dp[monoQ.back()]) {
                monoQ.pop_back();
            }
            monoQ.push_back(i);
        }

        return dp[n - 1];
    }
};
