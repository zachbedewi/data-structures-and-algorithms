class Solution {
public:
    int numberOfStableArrays(int zero, int one, int limit) {
        auto dp = vector(zero + 1, vector(one + 1, array<int, 2>{}));
        auto pfx0 = vector(zero + 1, vector<int64_t>(one + 1));
        auto pfx1 = vector(zero + 1, vector<int64_t>(one + 1));

        for (int i = 1; i <= min(zero, limit); ++i) {
            dp[i][0][0] = 1;
            pfx0[i][0] = pfx0[i - 1][0] + dp[i - 1][0][0];
        }
        for (int j = 1; j <= min(one, limit); ++j) {
            dp[0][j][1] = 1;
            pfx1[0][j] = pfx1[0][j - 1] + dp[0][j - 1][1];
        }

        for (int i = 1; i <= zero; ++i) {
            for (int j = 1; j <= one; ++j) {
                pfx0[i][j] = pfx0[i - 1][j] + dp[i - 1][j][1];
                pfx1[i][j] = pfx1[i][j - 1] + dp[i][j - 1][0];

                dp[i][j][0] = modsub(pfx0[i][j], pfx0[max(0, i - limit)][j]);
                dp[i][j][1] = modsub(pfx1[i][j], pfx1[i][max(0, j - limit)]);
            }
        }

        return (dp[zero][one][0] + dp[zero][one][1]) % MOD;
    }

private:
    static constexpr int MOD = 1e9 + 7;

    int modsub(const int64_t a, const int64_t b) {
        return static_cast<int>((a - b % MOD + MOD) % MOD);
    }
};
