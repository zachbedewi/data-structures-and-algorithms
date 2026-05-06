class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        ranges::sort(arr);
        const auto n = arr.size();

        auto elementToIndex { unordered_map<int, int>{} };
        for (const auto& [i, element] : views::enumerate(arr)) {
            elementToIndex[element] = i;
        }

        // dp[v] := The number of binary trees that can be rooted at v
        auto dp{ vector<long long>(n, 1) };

        for (const auto& [i, v] : views::enumerate(arr)) {
            for (const auto& [a, aI] : elementToIndex) {
                if (a < v && v % a == 0 && elementToIndex.contains(v / a)) {
                    const auto bI = elementToIndex[v / a];
                    dp[i] = (dp[i] + dp[aI] * dp[bI]) % MOD;
                }
            }
        }

        return ranges::fold_left(dp, 0LL, [](const auto acc, const auto x) {
            return (acc + x) % MOD;
        });
    }

private:
    static constexpr int MOD = 1e9 + 7;
};
