class Solution {
public:
    int distinctSequences(int n) {
        vector<vector<vector<int>>> memo(n + 1, vector<vector<int>>(7, vector<int>(7)));
        return dfs(memo, n);
    }

private:
    static constexpr int MOD = 1'000'000'007;

    int dfs(vector<vector<vector<int>>>& memo, int n, int prev = 0, int prevPrev = 0) {
        if (n == 0) {
            return 1;
        }
        if (memo[n][prev][prevPrev] != 0) {
            return memo[n][prev][prevPrev];
        }

        int res = 0;
        for (int curr = 1; curr < 7; ++curr) {
            if (curr != prev && curr != prevPrev && (prev == 0 || gcd(curr, prev) == 1)) {
                res = (res + dfs(memo, n - 1, curr, prev)) % MOD;
            }
        }
        return memo[n][prev][prevPrev] = res;
    }
};
