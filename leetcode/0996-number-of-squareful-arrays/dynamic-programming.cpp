class Solution {
public:
    int numSquarefulPerms(vector<int>& nums) {
        ranges::sort(nums);

        const int n = nums.size();
        vector<vector<int>> dp(1 << n, vector<int>(n));

        for (int i = 0; i < n; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            dp[1 << i][i] = 1;
        }

        const auto isSquare = [](const int x) {
            const int s = sqrt(x);
            return s * s == x || (s + 1) * (s + 1) == x;
        };

        for (int mask = 0; mask < (1 << n); ++mask) {
            for (int i = 0; i < n; ++i) {
                if (!(mask & (1 << i))) {
                    continue;
                }
                if (i > 0 && nums[i] == nums[i - 1] && !(mask & (1 << (i - 1)))) {
                    continue;
                }

                for (int j = 0; j < n; ++j) {
                    if (i == j || !(mask & (1 << j))) {
                        continue;
                    }
                    if (!isSquare(nums[i] + nums[j])) {
                        continue;
                    }
                    dp[mask][i] += dp[mask ^ (1 << i)][j];
                }
            }
        }

        int res = 0;
        const int fullMask = (1 << n) - 1;
        for (int i = 0; i < n; ++i) {
            res += dp[fullMask][i];
        }

        return res;
    }
};
