class Solution {
public:
    int characterReplacement(string s, int k) {
        unordered_map<char, int> count;

        int ans = 0;
        int maxFrequency = 0;
        for (int l = 0, r = 0; r < s.length(); ++r) {
            maxFrequency = max(maxFrequency, ++count[s[r]]);
            while (r - l + 1 - maxFrequency > k) {
                --count[s[l++]];
            }
            ans = max(ans, r - l + 1);
        }

        return ans;
    }
};
