class Solution {
public:
    int minimumDistance(string word) {
        const int n = word.length();
        vector<vector<vector<int>>> memo(27, vector<vector<int>>(27, vector<int>(n + 1)));

        for (int k = n - 1; k >= 0; --k) {
            const int to = word[k] - 'A';
            for (int i = 0; i < 27; ++i) {
                for (int j = 0; j < 27; ++j) {
                    const int costFromLeft = memo[to][j][k + 1] + cost(i, to);
                    const int costFromRight = memo[i][to][k + 1] + cost(j, to);
                    memo[i][j][k] = min(costFromLeft, costFromRight);
                }
            }
        }

        return memo[26][26][0];
    }

private:

    int cost(const int from, const int to) {
        // 26 indicates that the finger is currently hovering
        if (from == 26) {
            return 0;
        }
        return abs(from / 6 - to / 6) + abs(from % 6 - to % 6);
    }
};
