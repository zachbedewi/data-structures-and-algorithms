class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        unordered_map<int, int> elementToIndex{};
        for (const auto [idx, num] : views::enumerate(arr)) {
            elementToIndex[num] = idx;
        }

        const int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n, 2));

        int maxLength = 0;
        for (int i = 2; i < n; ++i) {
            for (int j = 1; j < i; ++j) {
                if (const auto it = elementToIndex.find(arr[i] - arr[j]); it != elementToIndex.end() && it->second < j) {
                    dp[i][j] = max(dp[i][j], dp[j][it->second] + 1);
                    maxLength = max(maxLength, dp[i][j]);
                }
            }
        }

        return maxLength >= 3 ? maxLength : 0;
    }
};
