class Solution {
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        const int n = nums.size();
        vector<int> dp(n, 0);
        dp[0] = nums[0];

        deque<int> decrease {{ 0 }};

        int res = nums[0];
        for (int i = 1; i < n; ++i) {
            if (i - decrease.front() > k) {
                decrease.pop_front();
            }

            dp[i] = nums[i] + max(0, dp[decrease.front()]);

            while (!decrease.empty() && dp[decrease.back()] < dp[i]) {
                decrease.pop_back();
            }

            decrease.push_back(i);
            res = max(res, dp[i]);
        }

        return res;
    }
};
