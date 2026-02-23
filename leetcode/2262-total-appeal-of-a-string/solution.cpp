class Solution {
public:
    long long appealSum(string s) {
        long long res = 0;
        long long curr = 0;
        vector<int> previousIndex(26, 0);

        for (int i = 0; i < s.length(); ++i) {
            curr += i - previousIndex[s[i] - 'a'] + 1;
            previousIndex[s[i] - 'a'] = i + 1;
            res += curr;
        }

        return res;
    }
};
