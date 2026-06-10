class Solution {
  public:
    int profitableSchemes(int n, int minProfit, vector<int> &group,
                          vector<int> &profit) {
        const auto numCrimes = profit.size();
        auto dp = vector(n + 1, vector<int>(minProfit + 1, 0));
        dp[0][0] = 1;

        for (int i = 0; i <= numCrimes - 1; ++i) {
            const int numPeopleRequired = group[i];
            const int crimeProfit = profit[i];
            for (int j = n; j >= 0; --j) {
                for (int p = 0; p <= minProfit; ++p) {
                    if (j - numPeopleRequired >= 0) {
                        dp[j][p] = (dp[j][p] + dp[j - numPeopleRequired]
                                                 [max(0, p - crimeProfit)]) %
                                   MOD;
                    }
                }
            }
        }

        int res = 0;
        for (int j = 0; j <= n; ++j) {
            res = (res + dp[j][minProfit]) % MOD;
        }
        return res;
    }

  private:
    static constexpr int MOD = 1e9 + 7;
};
