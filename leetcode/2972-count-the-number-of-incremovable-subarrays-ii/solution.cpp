class Solution {
  public:
    long long incremovableSubarrayCount(vector<int> &nums) {
        auto const n{nums.size()};
        auto const x{incPrefixIdx(nums)};

        if (x == nums.size() - 1) {
            return n * (n + 1) / 2;
        }

        auto y{incSuffixIdx(nums)};
        auto res{n - y + 1};
        for (auto i : std::views::iota(0uz, x + 1)) {
            while (y < n && nums[y] <= nums[i]) {
                ++y;
            }
            res += n - y + 1;
        }
        return res;
    }

  private:
    auto incPrefixIdx(std::span<const int> nums) -> std::size_t {
        auto res{0uz};
        while (res < nums.size() - 1 && nums[res] < nums[res + 1]) {
            ++res;
        }
        return res;
    }

    auto incSuffixIdx(std::span<const int> nums) -> std::size_t {
        auto res{nums.size() - 1};
        while (res > 0 && nums[res] > nums[res - 1]) {
            --res;
        }
        return res;
    }
};
