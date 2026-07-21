class Solution {
  public:
    string makeLargestSpecial(string s) {
        auto balance{0};
        auto l{0};
        vector<string> res;
        for (auto j = 0; j < s.length(); ++j) {
            if (s[j] == '1') {
                ++balance;
            } else {
                --balance;
            }

            if (balance == 0) {
                res.push_back(
                    '1' + makeLargestSpecial(s.substr(l + 1, j - l - 1)) + '0');
                l = j + 1;
            }
        }

        sort(res.rbegin(), res.rend());
        string out = "";
        for (int i = 0; i < res.size(); ++i) {
            out += res[i];
        }
        return out;
    }
};
