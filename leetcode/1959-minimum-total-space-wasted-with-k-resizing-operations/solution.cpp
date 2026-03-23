class Solution {
public:
    int minSpaceWastedKResizing(vector<int>& nums, int k) {
        vector<vector<int>> memo(nums.size(), vector<int>(k + 1, -1));
        return dfs(nums, 0, k, memo);
    }

private:

    static constexpr int kMax = 200'000'000;

    int dfs(vector<int>& nums, int i, int k, vector<vector<int>>& memo) {
        if (i == nums.size()) {
            return 0;
        }
        if (k == -1) {
            return kMax;
        }
        if (memo[i][k] != -1) {
            return memo[i][k];
        }

        int ans = kMax;
        int maxNum = nums[i];
        int totalSum = 0;
        for (int j = i; j < nums.size(); ++j) {
            maxNum = max(maxNum, nums[j]);
            totalSum += nums[j];
            int wasted = maxNum * (j - i + 1) - totalSum;
            ans = min(ans, dfs(nums, j + 1, k - 1, memo) + wasted);
        }

        return memo[i][k] = ans;
    }
};
