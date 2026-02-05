class Solution {
public:
    int minCost(vector<int>& nums, int k) {
        const int n = nums.size();
        unordered_map<int, int> valueToIndex;
        for (int i = 0; i < n; ++i) {
            auto it = valueToIndex.find(nums[i]);
            if (it == valueToIndex.end()) {
                it = valueToIndex.insert({nums[i], valueToIndex.size()}).first;
            }
            nums[i] = it->second;
        }
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;

        for (int i = 1; i <= nums.size(); ++i) {
            vector<int> count(valueToIndex.size(), 0);
            int cost = k;
            for (int j = i - 1; j >= 0; --j) {
                const int currCount = ++count[nums[j]];
                if (currCount == 2) {
                    cost += 2;
                } else if (currCount > 2) {
                    ++cost;
                }
                dp[i] = min(dp[i], dp[j] + cost);
            }
        }

        return dp[n];
    }
};
