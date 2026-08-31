class Solution {
  public:
    int minGroupsForValidAssignment(vector<int> &balls) {
        std::unordered_map<int, int> freq;
        for (auto const ball : balls) {
            ++freq[ball];
        }
        auto minFreq =
            std::ranges::min_element(
                freq, {}, &std::unordered_map<int, int>::value_type::second)
                ->second;

        auto res{std::numeric_limits<int>::max()};
        for (auto x : std::views::iota(1, minFreq + 1)) {
            auto boxes{calculateBoxes(freq, x)};
            if (boxes != -1) {
                res = std::min(res, boxes);
            }
        }

        return res;
    }

  private:
    auto calculateBoxes(std::unordered_map<int, int> const &frequencies, int x)
        -> int {
        auto boxes{0};
        for (auto const &[value, frequency] : frequencies) {
            auto a{frequency / (x + 1)};
            auto b{frequency % (x + 1)};

            if (b == 0) {
                boxes += a;
            } else if (x - b <= a) {
                boxes += a - (x - b);
                boxes += x - b + 1;
            } else {
                return -1;
            }
        }

        return boxes;
    }
};
