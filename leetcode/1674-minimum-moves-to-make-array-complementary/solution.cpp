class Solution {
  public:
    int minMoves(vector<int> &nums, int limit) {
        const auto n = nums.size();
        auto delta{vector<int>(2 * limit + 2, 0)};

        for (auto i{0uz}; i < n >> 1; ++i) {
            auto min = nums[i];
            auto max = nums[n - i - 1];
            if (min > max)
                swap(min, max);

            delta[2] += 2;
            --delta[min + 1];
            --delta[min + max];
            ++delta[min + max + 1];
            ++delta[max + limit + 1];
        }

        auto res = n;
        auto moves = 0uz;
        for (int target = 2; target <= limit * 2; ++target) {
            moves += delta[target];
            res = min(res, moves);
        }
        return res;
    }
};
