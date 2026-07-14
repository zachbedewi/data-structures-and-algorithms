class Solution {
  public:
    int bestRotation(vector<int> &nums) {
        auto n{nums.size()};
        vector<int> diff(n + 1, 0);

        for (int i = 0; i < n; ++i) {
            if (i - nums[i] >= 0) {
                diff[0] += 1;
                diff[i - nums[i] + 1] -= 1;
            }

            diff[i + 1] += 1;
            auto r{min(n, i - nums[i] + n + 1)};
            diff[r] -= 1;
        }

        vector<int> pref(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            pref[i] = pref[i - 1] + diff[i - 1];
        }

        auto res{0};
        auto maxCount{0};
        for (int i = 0; i <= n; ++i) {
            if (pref[i] > maxCount) {
                maxCount = pref[i];
                res = i - 1;
            }
        }

        return res;
    }
};
