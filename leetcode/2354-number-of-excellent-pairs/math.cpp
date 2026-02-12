class Solution {
public:
    long long countExcellentPairs(vector<int>& nums, int k) {
        vector<long long> count(33, 0);
        for (const auto num : unordered_set<int> {nums.begin(), nums.end()}) {
            ++count[__builtin_popcount(num)];
        }

        long long res = 0;
        for (int i = 1; i < 33; ++i) {
            for (int j = max(k - i, i); j < 33; ++j) {
                res += count[i] * count[j] * (i == j ? 1 : 2);
            }
        }

        return res;
    }
};
