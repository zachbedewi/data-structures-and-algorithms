class Solution {
  public:
    int numWays(vector<string> &words, string target) {
        auto const wordLength = words[0].length();

        vector<vector<long>> dp(target.length() + 1,
                                vector<long>(wordLength + 1, 0));
        vector<vector<int>> counts(wordLength, vector<int>(26, 0));

        for (auto const word : words) {
            for (auto i{0uz}; i < wordLength; ++i) {
                ++counts[i][word[i] - 'a'];
            }
        }

        dp[0][0] = 1;
        for (int i = 0; i <= target.length(); ++i) {
            for (int j = 0; j < wordLength; ++j) {
                if (i < target.length()) {
                    dp[i + 1][j + 1] =
                        dp[i][j] * counts[j][target[i] - 'a'] % MOD;
                }
                dp[i][j + 1] = (dp[i][j + 1] + dp[i][j]) % MOD;
            }
        }

        return dp[target.length()][wordLength];
    }

  private:
    static constexpr int MOD{1'000'000'007};
};
