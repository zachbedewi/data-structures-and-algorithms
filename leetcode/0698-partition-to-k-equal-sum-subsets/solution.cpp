class Solution {
  public:
    bool canPartitionKSubsets(vector<int> &nums, int k) {
        const auto sum = ranges::fold_left(nums, 0, std::plus<>{});
        if (sum % k != 0) {
            return false;
        }

        const auto n = nums.size();
        auto memo = vector<char>(1 << n, -1);
        memo[(1 << n) - 1] = 1;

        ranges::sort(nums, std::greater<>{});
        return solve(nums, sum / k, memo, 0, 0);
    }

  private:
    bool solve(const vector<int> &nums, int target, vector<char> &memo,
               int mask, int currentSum) {
        if (memo[mask] != -1) {
            return memo[mask];
        }

        for (int i = 0; i < nums.size(); ++i) {
            if ((mask & (1 << i)) != 0 || nums[i] > target ||
                (currentSum % target) + nums[i] > target) {
                continue;
            }

            if (solve(nums, target, memo, mask | (1 << i),
                      currentSum + nums[i]) == 1) {
                memo[mask] = 1;
                break;
            }
        }
        memo[mask] = memo[mask] == -1 ? 0 : memo[mask];

        return memo[mask] == 1;
    }
};
