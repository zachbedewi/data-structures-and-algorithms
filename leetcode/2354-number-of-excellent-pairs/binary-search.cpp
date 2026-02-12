class Solution {
public:
    long long countExcellentPairs(vector<int>& nums, int k) {
        vector<long long> count;
        for(const auto num : unordered_set<int> {nums.begin(), nums.end()}){
            count.push_back(__builtin_popcount(num));
        }
        ranges::sort(count);
        const int n = count.size();

        long long res = 0;
        for (const auto bitCount : count) {
            const auto remain = k - bitCount;
            const auto it = ranges::lower_bound(count, remain);

            if (it != count.end()) {
                res += n - distance(count.begin(), it);
            }
        }

        return res;
    }
};
