class Solution {
public:
    int shortestMatchingSubstring(string s, string p) {
        const auto [a, b, c] = split(p);
        const int ns = s.length();
        const int na = a.length();
        const int nb = b.length();
        const int nc = c.length();

        vector<int> lpsA = computeLps(a + '#' + s);
        vector<int> lpsB = computeLps(b + '#' + s);
        vector<int> lpsC = computeLps(c + '#' + s);

        int res = numeric_limits<int>::max();
        for (int i = 0, j = 0, k = 0; i + nb + nc < ns; ++i) {
            while (i < ns && lpsA[na + 1 + i] != na) {
                ++i;
            }
            while (j < ns && (j < i + nb || lpsB[nb + 1 + j] != nb)) {
                ++j;
            }
            while (k < ns && (k < j + nc || lpsC[nc + 1 + k] != nc)) {
                ++k;
            }
            if (k == ns) {
                break;
            }
            // i is at the end of the string matching a, so we need to add
            // the length of the prefix to the total length;
            res = min(res, k - i + na);
        }

        return res == numeric_limits<int>::max() ? -1 : res;
    }

private:
    vector<int> computeLps(const string& s) {
        const int n = s.length();
        vector<int> lps(n);

        for (int i = 1; i < n; ++i) {
            int j = lps[i - 1];
            while (j > 0 && s[i] != s[j]) {
                j = lps[j - 1];
            }
            if (s[i] == s[j]) {
                lps[i] = ++j;
            }
        }

        return lps;
    }

    tuple<string, string, string> split(const string& pattern) {
        const int i = pattern.find('*');
        const int j = pattern.find('*', i + 1);
        return {pattern.substr(0, i), pattern.substr(i + 1, j - i - 1), pattern.substr(j + 1)};
    }
};
