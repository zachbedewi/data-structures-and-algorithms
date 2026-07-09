class Solution {
  public:
    string decodeAtIndex(string s, int k) {
        long length = 0;
        int i = 0;
        for (; length < k; ++i) {
            if (isdigit(s[i])) {
                length *= s[i] - '0';
            } else {
                ++length;
            }
        }

        while (i--) {
            if (isdigit(s[i])) {
                length /= s[i] - '0';
                k %= length;
            } else {
                if (k % length == 0) {
                    return string(1, s[i]);
                }
                --length;
            }
        }

        return "";
    }
};
