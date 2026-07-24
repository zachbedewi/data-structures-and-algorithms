class Solution {
  public:
    int bestTeamScore(vector<int> &scores, vector<int> &ages) {
        auto const n = scores.size();
        vector<pair<int, int>> players;
        for (auto i{0uz}; i < n; ++i) {
            players.emplace_back(ages[i], scores[i]);
        }
        ranges::sort(players, greater{});

        vector<int> dp(n, 0);
        auto res = 0;
        for (auto i{0uz}; i < n; ++i) {
            dp[i] = players[i].second;
            for (auto j{0uz}; j < i; ++j) {
                if (players[j].second >= players[i].second) {
                    dp[i] = max(dp[i], dp[j] + players[i].second);
                }
            }
            res = max(res, dp[i]);
        }
        return res;
    }
};
