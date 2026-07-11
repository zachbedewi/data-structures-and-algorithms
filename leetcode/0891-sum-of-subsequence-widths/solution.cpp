class Solution {
  public:
    int sumSubseqWidths(vector<int> &nums) {
        ranges::sort(nums);
        const int n = nums.size();
        long res = 0;
        long subsetFactor = 1;

        for (int i = 0; i < n; ++i, subsetFactor = subsetFactor * 2 % MOD) {
            res = (res + nums[i] * subsetFactor -
                   nums[n - i - 1] * subsetFactor) %
                  MOD;
        }

        return (res + MOD) % MOD;
    }

  private:
    static constexpr int MOD = 1e9 + 7;
};
