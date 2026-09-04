class Solution {
  public:
    vector<int> recoverArray(vector<int> &nums) {
        auto const n{nums.size() / 2};
        std::ranges::sort(nums);

        std::unordered_map<int, int> counts;
        for (auto const num : nums) {
            ++counts[num];
        }

        auto const lower{nums[0]};

        for (auto const i : std::views::iota(1uz, nums.size())) {
            auto higher{nums[i]};
            if ((higher - lower) % 2 != 0) {
                continue;
            }

            auto k{(higher - lower) / 2};
            if (k <= 0) {
                continue;
            }

            auto res = check(k, n, nums, counts);
            if (!res.empty()) {
                return res;
            }
        }

        throw;
    }

  private:
    auto check(int k, int n, std::vector<int> const &nums,
               std::unordered_map<int, int> counts) -> std::vector<int> {
        std::vector<int> res;

        for (auto const num : nums) {
            if (counts[num] <= 0) {
                continue;
            }

            auto higher{num + 2 * k};
            if (counts[higher] <= 0) {
                return {};
            }

            --counts[num];
            --counts[higher];
            res.push_back(num + k);
        }

        return res;
    }
};
