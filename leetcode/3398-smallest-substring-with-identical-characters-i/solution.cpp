class Solution {
public:
    int minLength(string s, int numOps) {
        int l = 1;
        int r = s.length();

        while (l < r) {
            int m = l + (r - l) / 2;
            if (getMinOps(s, m) <= numOps) {
                r = m;
            } else {
                l = m + 1;
            }
        }

        return l;
    }

private:
    int getMinOps(const string& s, int k) {
        if (k == 1) {
            size_t res = 0;
            for (int i = 0; i < s.length(); ++i) {
                if (s[i] - '0' != i % 2) {
                    ++res;
                }
            }
            return min(res, s.length() - res);
        }

        int res = 0;
        int runningLength = 1;
        for (int i = 1; i < s.length(); ++i) {
            if (s[i] == s[i - 1]) {
                ++runningLength;
            } else {
                res += runningLength / (k + 1);
                runningLength = 1;
            }
        }
        return res + runningLength / (k + 1);
    }
};
