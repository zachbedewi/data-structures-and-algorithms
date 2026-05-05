class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        const string upperLimit = to_string(n);
        const int numDigitsInUpperLimit = upperLimit.size();
        const int numDigitChoices = digits.size();
        int res = 0;

        for (int i = 1; i < numDigitsInUpperLimit; ++i) {
            res += pow(numDigitChoices, i);
        }

        for (int d = 0; d < numDigitsInUpperLimit; ++d) {
            bool startWithSameNum = false;
            for (const auto& digit : digits) {
                if (digit[0] < upperLimit[d]) {
                    res += pow(numDigitChoices, numDigitsInUpperLimit - d - 1);
                } else if (digit[0] == upperLimit[d]) {
                    startWithSameNum = true;
                }
            }
            if (!startWithSameNum) {
                return res;
            }
        }

        return res + 1;
    }
};
