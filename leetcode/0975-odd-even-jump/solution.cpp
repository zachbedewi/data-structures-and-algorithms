class Solution {
  public:
    int oddEvenJumps(vector<int> &arr) {
        const auto n = arr.size();

        vector<vector<bool>> dp(n, vector<bool>(2, false));
        dp[n - 1][0] = dp[n - 1][1] = true;

        std::map<int, int> valToIdx{};
        valToIdx[arr[n - 1]] = n - 1;

        int res = 1;
        for (int i = n - 2; i >= 0; --i) {
            if (auto it = valToIdx.lower_bound(arr[i]); it != valToIdx.end()) {
                dp[i][1] = dp[it->second][0];
            }

            if (auto it = valToIdx.upper_bound(arr[i]);
                it != valToIdx.begin()) {
                --it;
                dp[i][0] = dp[it->second][1];
            }

            if (dp[i][1]) {
                ++res;
            }

            valToIdx[arr[i]] = i;
        }

        return res;
    }
};
