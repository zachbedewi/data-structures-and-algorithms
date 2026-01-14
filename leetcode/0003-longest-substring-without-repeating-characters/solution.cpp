class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> lastSeen;
        int l = -1;
        int maxLength = 0;

        for (int r = 0; r < s.length(); ++r) {
            if (const auto it = lastSeen.find(s[r]); it != lastSeen.end()) {
                l = max(l, it->second);
            }
            lastSeen[s[r]] = r;
            maxLength = max(maxLength, r - l);
        }

        return maxLength;
    }
};
