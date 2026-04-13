class Solution {
public:
    int numberOfBeautifulIntegers(int low, int high, int k) {
        const string lowStr = to_string(low);
        const string highStr = to_string(high);
        const string lowWithLeadingZeros =
            string(highStr.length() - lowStr.length(), '0') + lowStr;
        vector<vector<vector<vector<vector<vector<int>>>>>> memo(
            highStr.length(),
            vector<vector<vector<vector<vector<int>>>>>(
                10,
                vector<vector<vector<vector<int>>>>(
                    10, vector<vector<vector<int>>>(
                            k, vector<vector<int>>(2, vector<int>(2, -1))))));

        return count(lowWithLeadingZeros, highStr, k, 0, 0, 0, 0, true, true,
                     true, memo);
    }

private:
    int count(const string& low, const string& high, int k, int i, int even,
              int odd, int remainder, bool isLeadingZero, bool tight1,
              bool tight2,
              vector<vector<vector<vector<vector<vector<int>>>>>>& memo) {
        if (i == high.length()) {
            return !isLeadingZero && even == odd && remainder == 0;
        }
        if (memo[i][even][odd][remainder][tight1][tight2] != -1) {
            return memo[i][even][odd][remainder][tight1][tight2];
        }

        int res = 0;
        const int minDigit = tight1 ? low[i] - '0' : 0;
        const int maxDigit = tight2 ? high[i] - '0' : 9;

        for (int d = minDigit; d <= maxDigit; ++d) {
            const int nextEven =
                even + ((!isLeadingZero || d > 0) && d % 2 == 0);
            const int nextOdd = odd + (d % 2 == 1);
            const int nextRemainder = (remainder * 10 + d) % k;
            const bool nextTight1 = tight1 && (d == minDigit);
            const bool nextTight2 = tight2 && (d == maxDigit);
            res += count(low, high, k, i + 1, nextEven, nextOdd, nextRemainder,
                         isLeadingZero && d == 0, nextTight1, nextTight2, memo);
        }

        return memo[i][even][odd][remainder][tight1][tight2] = res;
    }
};
