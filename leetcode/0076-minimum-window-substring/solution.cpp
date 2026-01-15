class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> count;

        for (const char c : t) {
            ++count[c];
        }

        int minLength = INT_MAX;
        int maxLeftStart = -1;
        int required = t.length();
        for (int r = 0, l = 0; r < s.length(); ++r) {
            if (--count[s[r]] >= 0) {
                --required;
            }
            while (required == 0) {
                if (r - l + 1 < minLength) {
                    maxLeftStart = l;
                    minLength = r - l + 1;
                }
                if (++count[s[l++]] > 0) {
                    ++required;
                }
            }
        }

        return maxLeftStart == -1 ? "" : s.substr(maxLeftStart, minLength);
    }
};
