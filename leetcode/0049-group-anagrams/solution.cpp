class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> letterCountToWords;

        for (const auto& s : strs) {
            vector<int> letterCounts(26, 0);
            for (const auto& c : s) {
                letterCounts[c - 'a']++;
            }

            string key = to_string(letterCounts[0]);
            for (int i = 1; i < letterCounts.size(); i++) {
                key += ',' + to_string(letterCounts[i]);
            }
            letterCountToWords[key].push_back(s);
        }

        vector<vector<string>> result;
        for (const auto& pair : letterCountToWords) {
            result.push_back(pair.second);
        }
        return result;
    }
};
