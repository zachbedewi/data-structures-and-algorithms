class Solution {
  public:
    bool isTransformable(string s, string t) {
        std::vector<std::queue<int>> digitToIndices(10);
        for (int i = 0; i < s.length(); ++i) {
            digitToIndices[s[i] - '0'].push(i);
        }

        for (const auto c : t) {
            const auto d = c - '0';
            if (digitToIndices[d].empty())
                return false;
            for (auto s{0uz}; s < d; ++s) {
                if (!digitToIndices[s].empty() &&
                    digitToIndices[s].front() < digitToIndices[d].front())
                    return false;
            }
            digitToIndices[d].pop();
        }
        return true;
    }
};
