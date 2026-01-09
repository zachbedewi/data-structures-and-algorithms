class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> res;
        if (s.length() < 10) {
            return res;
        }

        unordered_map<string, int> seen;

        for (int i = 0; i <= s.length() - 10; ++i) {
            string substring = s.substr(i, 10);
            if (const auto it = seen.find(substring); it != seen.end() && it->second == 1) {
                res.push_back(it->first);
            }
            ++seen[substring];
        }

        return res;
    }
};
