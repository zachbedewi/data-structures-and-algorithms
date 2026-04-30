class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        const int n = stations.size();
        vector<long long> dp(n + 1);
        dp[0] = startFuel;

        for (int i = 0; i < n; ++i) {
            for (int t = i; t >= 0 && dp[t] >= stations[i][0]; --t) {
                dp[t + 1] = max(dp[t + 1], dp[t] + stations[i][1]);
            }
        }

        for (int t = 0; t <= n; ++t) {
            if (dp[t] >= target) {
                return t;
            }
        }

        return -1;
    }
};
