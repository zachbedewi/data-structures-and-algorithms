class Solution {
  public:
    int countSpecialSubsequences(vector<int> &nums) {
        auto const n = nums.size();
        vector<int> dp(3, 0);

        for (auto const num : nums) {
            dp[num] = ((2 * dp[num]) % MOD + (num > 0 ? dp[num - 1] : 1)) % MOD;
        }

        return dp[2];
    }

  private:
    static constexpr int MOD{1'000'000'007};
};
