class Solution {
  public:
    vector<string> expand(string s) {
        std::string curr("");
        std::vector<std::string> res;
        solve(s, 0uz, curr, res);
        return res;
    }

  private:
    void solve(std::string const &s, std::size_t i, std::string &curr,
               std::vector<std::string> &res) {
        if (i == s.length()) {
            res.push_back(curr);
            return;
        }

        if (s[i] == '{') {
            std::vector<char> charList;
            auto nextIndex{i + 1};
            while (nextIndex < s.length() && s[nextIndex] != '}') {
                if (s[nextIndex] != ',') {
                    charList.push_back(s[nextIndex]);
                }
                ++nextIndex;
            }
            ++nextIndex;
            std::ranges::sort(charList);

            for (auto const c : charList) {
                curr.push_back(c);
                solve(s, nextIndex, curr, res);
                curr.pop_back();
            }
        } else {
            curr.push_back(s[i]);
            solve(s, i + 1, curr, res);
            curr.pop_back();
        }
    }
};
