class Solution {
public:
    int uniqueLetterString(string s) {
        const int n = s.length();
        vector<long long> previousLeft(26, -1);
        vector<long long> previousRight(26, n);
        vector<long long> leftCount(n, -1);
        vector<long long> rightCount(n, -1);

        for (int i = 0; i < n; ++i) {
            leftCount[i] = i - previousLeft[s[i] - 'A'];
            previousLeft[s[i] - 'A'] = i;
        }
        for (int i = n - 1; i >= 0; --i) {
            rightCount[i] = previousRight[s[i] - 'A'] - i;
            previousRight[s[i] - 'A'] = i;
        }

        int res = 0;
        for (int i = 0; i < n; ++i) {
            res += leftCount[i] * rightCount[i];
        }
        return res;
    }
};
