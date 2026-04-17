class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        ranges::sort(envelopes, [](const auto& a, const auto& b) {
            return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
        });

        vector<int> dp;
        for (const auto& envelope : envelopes) {
            const int height = envelope[1];
            if (dp.empty() || height > dp.back()) {
                dp.push_back(height);
            } else {
                const int idx = ranges::lower_bound(dp, height) - dp.begin();
                dp[idx] = height;
            }
        }

        return dp.size();
    };
};
