class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        const int n = piles.size();
        vector<int> suffixSum = piles;
        for (int i = n - 2; i >= 0; --i) {
            suffixSum[i] += suffixSum[i + 1];
        }

        // memo[i][j] := maximum number of stones Alice can get when starting at index
        // with M = j
        vector<vector<int>> memo(n, vector<int>(n + 1, 0));
        dfs(piles, memo, suffixSum, 0, 1);

        return memo[0][1];
    }

private:
    int dfs(vector<int>& piles, vector<vector<int>>& memo, vector<int>& suffixSum, int i, int M) {
        if (i >= piles.size()) {
            return 0;
        }
        if (2 * M >= piles.size() - i) {
            return memo[i][M] = suffixSum[i];
        }
        if (memo[i][M]) {
            return memo[i][M];
        }

        int minStonesForOpponent = numeric_limits<int>::max();
        for (int X = 1; X <= 2 * M; ++X) {
            minStonesForOpponent = min(minStonesForOpponent, dfs(piles, memo, suffixSum, i + X, max(M, X)));
        }

        return memo[i][M] = suffixSum[i] - minStonesForOpponent;
    }
};
