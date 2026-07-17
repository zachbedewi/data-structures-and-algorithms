class Solution {
  public:
    int smallestRangeII(vector<int> &nums, int k) {
        auto const n = nums.size();
        ranges::sort(nums);

        auto minScore{numeric_limits<int>::max()};
        for (auto pivot{0uz}; pivot <= n; ++pivot) {
            auto firstMinChoice = pivot == 0 ? nums[0] - k : nums[0] + k;
            auto secondMinChoice =
                pivot == n ? numeric_limits<int>::max() : nums[pivot] - k;
            auto minElement = min(firstMinChoice, secondMinChoice);

            auto firstMaxChoice =
                pivot == n ? nums[n - 1] + k : nums[n - 1] - k;
            auto secondMaxChoice =
                pivot == 0 ? numeric_limits<int>::min() : nums[pivot - 1] + k;
            auto maxElement = max(firstMaxChoice, secondMaxChoice);

            minScore = min(minScore, maxElement - minElement);
        }

        return minScore;
    }
};
