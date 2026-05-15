class Solution {
public:
    int distinctSubseqII(string s) {
        const int n = s.length();
        vector<long long> dp(n, 0);
        array<int, 26> last;
        last.fill(-1);

        dp[0] = 1;
        last[s[0] - 'a'] = 0;

        for (int i = 1; i < n; ++i) {
            const int c = s[i] - 'a';
            dp[i] = (2 * dp[i - 1] + 1) % MOD;
            if (last[c] != -1) {
                const int sub = last[c] > 0 ? dp[last[c] - 1] + 1 : 1;
                dp[i] = (dp[i] - sub % MOD + MOD) % MOD;
            }
            last[c] = i;
        }

        return dp[n - 1];
    }

private:
    static constexpr int MOD = 1e9 + 7;
};
