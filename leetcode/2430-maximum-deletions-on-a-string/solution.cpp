class Solution {
public:
    int deleteString(string s) {
        const int n = s.length();
        vector<vector<int>> lcs(n + 1, vector<int>(n + 1, 0));
        vector<int> memo(n, 1);

        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                if (s[i] == s[j]) {
                    lcs[i][j] = lcs[i + 1][j + 1] + 1;
                }
                if (lcs[i][j] >= j - i) {
                    memo[i] = max(memo[i], memo[j] + 1);
                }
            }
        }

        return memo[0];
    }
};
