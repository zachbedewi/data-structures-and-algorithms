class Solution {
  public:
    string smallestSubsequence(string s) {
        array<int, 26> last;
        array<bool, 26> used;
        for (int i = 0; i < s.length(); ++i) {
            last[s[i] - 'a'] = i;
        }

        string res = "";
        for (int i = 0; i < s.length(); ++i) {
            if (used[s[i] - 'a'])
                continue;
            used[s[i] - 'a'] = true;
            while (!res.empty() && s[i] < res.back() &&
                   i < last[res.back() - 'a']) {
                used[res.back() - 'a'] = false;
                res.pop_back();
            }
            res.push_back(s[i]);
        }
        return res;
    }
};
