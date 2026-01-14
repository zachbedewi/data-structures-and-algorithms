class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        vector<int> count(26, 0);

        for (const char c : s1) {
            ++count[c - 'a'];
        }

        int required = s1.length();
        for (int r = 0; r < s2.length(); ++r) {
            if (--count[s2[r] - 'a'] >= 0) {
                --required;
            }
            if (r >= s1.length()) {
                if (++count[s2[r - s1.length()] - 'a'] > 0) {
                    ++required;
                }
            }
            if (required == 0) {
                return true;
            }
        }

        return false;
    }
};
