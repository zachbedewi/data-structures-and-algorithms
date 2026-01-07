class Solution {
public:
    int minSwaps(string s) {
        int zeroCount = 0;
        int oneCount = 0;
        for (const auto c : s) {
            c == '0' ? ++zeroCount : ++oneCount;
        }
        if (abs(zeroCount - oneCount) > 1) {
            return -1;
        }

        if (zeroCount > oneCount) {
            return countIncorrect(s, '0');
        }
        if (oneCount > zeroCount) {
            return countIncorrect(s, '1');
        }
        return min(countIncorrect(s, '0'), countIncorrect(s, '1'));
    }

private:
    int countIncorrect(const string& s, const char referenceCharacter) {
        int numIncorrect = 0;
        for (int i = 0; i < s.length(); i += 2) {
            if (s[i] != referenceCharacter) {
                ++numIncorrect;
            }
        }
        return numIncorrect;
    }
};
