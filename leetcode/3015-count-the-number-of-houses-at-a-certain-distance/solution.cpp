class Solution {
public:
    vector<int> countOfPairs(int n, int x, int y) {
        vector<int> res(n, 0);

        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                const int minDist = min({abs(i - j), abs(i - x) + 1 + abs(y - j), abs(i - y) + 1 + abs(x - j)});
                res[minDist - 1] += 2;
            }
        }

        return res;
    }
};
