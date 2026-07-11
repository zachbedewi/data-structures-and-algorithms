class Solution {
  public:
    int maxDigitRange(vector<int> &nums) {
        unordered_map<int, vector<int>> rangeToNums;

        int maxRange = numeric_limits<int>::min();

        for (const auto num : nums) {
            int range = digitRange(num);
            maxRange = max(maxRange, range);
            rangeToNums[range].push_back(num);
        }

        return accumulate(rangeToNums[maxRange].begin(),
                          rangeToNums[maxRange].end(), 0);
    }

  private:
    int digitRange(int num) {
        int maxD = numeric_limits<int>::min();
        int minD = numeric_limits<int>::max();
        while (num) {
            int digit = num % 10;
            maxD = max(maxD, digit);
            minD = min(minD, digit);
            num /= 10;
        }
        return maxD - minD;
    }
};
