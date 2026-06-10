class Solution {
  public:
    int myAtoi(string s) {
        bool started = false;
        bool isNegative = false;

        int res = 0;
        for (int i = 0; i < s.length(); ++i) {
            if (!started && isspace(s[i])) {
                continue;
            } else if (isspace(s[i])) {
                break;
            } else if (!started && (s[i] == '-' || s[i] == '+')) {
                isNegative = s[i] == '-';
                started = true;
            } else if (!isdigit(s[i])) {
                break;
            } else {
                started = true;
                long long intermediate =
                    static_cast<long>(res) * 10 + convertToDigit(s[i]);
                if (!isNegative && intermediate >= numeric_limits<int>::max()) {
                    return numeric_limits<int>::max();
                } else if (isNegative &&
                           -intermediate <= numeric_limits<int>::min()) {
                    return numeric_limits<int>::min();
                } else {
                    res = intermediate;
                }
            }
        }

        return isNegative ? -res : res;
    }

  private:
    int convertToDigit(const char d) {
        if (d == '0') {
            return 0;
        } else if (d == '1') {
            return 1;
        } else if (d == '2') {
            return 2;
        } else if (d == '3') {
            return 3;
        } else if (d == '4') {
            return 4;
        } else if (d == '5') {
            return 5;
        } else if (d == '6') {
            return 6;
        } else if (d == '7') {
            return 7;
        } else if (d == '8') {
            return 8;
        } else {
            return 9;
        }
    }
};
