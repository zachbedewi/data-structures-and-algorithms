class Solution {
public:
    string shortestSuperstring(vector<string>& words) {
        const int n = words.size();
        vector<vector<int>> dp(1 << n, vector<int>(n, numeric_limits<int>::max()));
        vector<vector<int>> path(1 << n, vector<int>(n, -1));

        const auto overlap = computeOverlaps(words);

        for (int i = 0; i < n; ++i) {
            dp[(1 << i)][i] = words[i].length();
        }

        for (int i = 1; i < (1 << n); ++i) {
            for (int j = 0; j < n; ++j) {
                if ((i & (1 << j)) != 0) {
                    for (int k = 0; k < n; ++k) {
                        if ((i & (1 << k)) == 0) {
                            const int newMask = i | (1 << k);
                            const int newLen = dp[i][j] + words[k].length() - overlap[j][k];
                            if (newLen < dp[newMask][k]) {
                                dp[newMask][k] = newLen;
                                path[newMask][k] = j;
                            }
                        }
                    }
                }
            }
        }

        const int fullMask = (1 << n) - 1;
        int last = distance(dp[fullMask].begin(), ranges::min_element(dp[fullMask]));

        vector<int> order;
        for (int mask = fullMask, curr = last; curr != -1;) {
            order.push_back(curr);
            int prev = path[mask][curr];
            mask ^= (1 << curr);
            curr = prev;
        }
        ranges::reverse(order);

        string res = words[order[0]];
        for (int i = 1; i < n; ++i) {
            res += words[order[i]].substr(overlap[order[i - 1]][order[i]]);
        }

        return res;
    }

private:
    vector<vector<int>> computeOverlaps(const vector<string>& words) {
        const int n = words.size();
        vector<vector<int>> overlap(n, vector<int>(n, 0));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j == i) {
                    continue;
                }

                const auto& wordI = words[i];
                const auto wordILen = wordI.length();

                const auto& wordJ = words[j];
                const auto wordJLen = wordJ.length();

                const auto maxLen = min(wordILen, wordJLen);
                for (int k = maxLen; k >= 1; --k) {
                    if (wordI.substr(wordILen - k) == wordJ.substr(0, k)) {
                        overlap[i][j] = k;
                        break;
                    }
                }
            }
        }

        return overlap;
    }
};
