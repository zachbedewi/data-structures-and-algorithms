class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        const int n = stoneValue.size();

        // memo[i] := The overall score of the game when starting from index i
        vector<int> memo(n, numeric_limits<int>::min());

        const auto score = dfs(stoneValue, memo, 0);
        if (score == 0) {
            return "Tie";
        } else if (score > 0) {
            return "Alice";
        } else {
            return "Bob";
        }
    }

private:
    int dfs(vector<int>& stoneValue, vector<int>& memo, int i) {
        if (i >= stoneValue.size()) {
            return 0;
        }
        if (memo[i] == numeric_limits<int>::min()) {
            for (int toTake = 0, sum = 0; toTake < 3 && i + toTake < stoneValue.size(); ++toTake) {
                sum += stoneValue[i + toTake];
                memo[i] = max(memo[i], sum - dfs(stoneValue, memo, i + toTake + 1));
            }
        }

        return memo[i];
    }
};
