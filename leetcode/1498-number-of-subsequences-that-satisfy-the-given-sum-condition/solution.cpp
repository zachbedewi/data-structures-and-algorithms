class Solution {
  public:
    int numSubseq(vector<int> &nums, int target) {
        auto const n = nums.size();
        ranges::sort(nums);

        vector<int> pow2(n, 1);
        for (int i = 1; i < n; ++i) {
            pow2[i] = (pow2[i - 1] * 2) % mod;
        }

        int res = 0;
        for (int i = 0; i < nums.size(); ++i) {
            auto it =
                upper_bound(nums.begin() + i, nums.end(), target - nums[i]);
            auto j = distance(nums.begin(), it) - 1;
            if (j < i)
                break;

            res = (res + pow2[j - i]) % mod;
        }

        return res;
    }

  private:
    static constexpr int mod{1'000'000'000 + 7};
};
