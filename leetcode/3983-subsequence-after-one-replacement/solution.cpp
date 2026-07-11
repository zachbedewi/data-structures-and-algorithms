class Solution {
  public:
    bool canMakeSubsequence(string s, string t) {
        auto const n = s.length();
        auto i = 0;
        auto j = 0;

        for (auto const &c : t) {
            j = max(j + (j < n && c == s[j] ? 1 : 0), i + 1);
            i += (i < n && c == s[i] ? 1 : 0);
        }
        return j >= n;
    }
};
