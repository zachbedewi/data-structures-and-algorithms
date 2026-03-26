class Solution {
public:
    int minimumFinishTime(vector<vector<int>>& tires, int changeTime, int numLaps) {
        vector<int> singleTire(numLaps + 1, numeric_limits<int>::max() / 2);
        for (int i = 0; i < tires.size(); ++i) {
            const int f = tires[i][0];
            const int r = tires[i][1];
            int totalTime = 0;
            // Represents r^(x - 1)
            int rExponent = 1;
            for (int j = 1; j <= numLaps; ++j) {
                if (static_cast<long>(f) * rExponent >= changeTime + f) {
                    break;
                }
                totalTime += f * rExponent;
                rExponent *= r;
                singleTire[j] = min(singleTire[j], totalTime);
            }
        }

        vector<int> dp(numLaps + 1, numeric_limits<int>::max() / 2);
        dp[0] = 0;
        for (int i = 1; i <= numLaps; ++i) {
            for (int j = 1; j <= i; ++j) {
                dp[i] = min(dp[i], dp[i - j] + changeTime + singleTire[j]);
            }
        }
        return dp[numLaps] - changeTime;
    }
};
