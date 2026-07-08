class Solution {
  public:
    int minimumIncrements(vector<int> &nums, vector<int> &target) {
        const auto k = target.size();
        auto lcms = precomputeLcm(nums, target);

        auto dp =
            vector<long long>(1 << k, std::numeric_limits<long long>::max());
        dp[0] = 0;

        for (const auto num : nums) {
            auto maskCost{vector<pair<long long, long long>>{}};
            for (auto mask{1uz}; mask < (1 << k); ++mask) {
                auto currLcm = lcms[mask];
                auto cost = num % currLcm == 0 ? 0 : currLcm - (num % currLcm);
                maskCost.emplace_back(mask, cost);
            }

            auto newDp = dp;
            for (auto mask = 0; mask < (1 << k); ++mask) {
                if (dp[mask] == numeric_limits<long long>::max())
                    continue;
                for (const auto &[newMask, cost] : maskCost) {
                    auto combinedMask = mask | newMask;
                    auto combinedCost = dp[mask] + cost;
                    if (combinedCost < newDp[combinedMask]) {
                        newDp[combinedMask] = combinedCost;
                    }
                }
            }

            dp = newDp;
        }

        const auto fullMask = (1 << k) - 1;
        return dp[fullMask] == numeric_limits<long long>::max() ? -1
                                                                : dp[fullMask];
    }

  private:
    auto precomputeLcm(const std::vector<int> &nums,
                       const std::vector<int> &target)
        -> std::vector<long long> {
        const auto k = target.size();
        auto res = vector<long long>(1 << k, 0);
        for (auto mask{1uz}; mask < (1 << k); ++mask) {
            auto subset{std::vector<long long>{}};
            for (auto i{0uz}; i < k; ++i) {
                if (mask & (1 << i)) {
                    subset.emplace_back(target[i]);
                }
            }

            auto currLcm = subset[0];
            for (const auto t : subset) {
                currLcm = std::lcm(currLcm, t);
            }
            res[mask] = currLcm;
        }
        return res;
    }
};
