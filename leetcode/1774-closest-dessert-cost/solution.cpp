class Solution {
public:
    int closestCost(vector<int>& baseCosts, vector<int>& toppingCosts,
                    int target) {
        int best = INT_MAX;
        for (const auto base : baseCosts) {
            dfs(toppingCosts, 0, base, target, best);
        }
        return best;
    }

private:
    void dfs(const vector<int>& toppingCosts, int i, int cost, int target,
             int& best) {
        if (cost >= target || i >= toppingCosts.size()) {
            if (abs(cost - target) < abs(best - target)) {
                best = cost;
            } else if (abs(cost - target) == abs(best - target)) {
                best = min(best, cost);
            }
            return;
        }

        for (int j = 0; j <= 2; ++j) {
            dfs(toppingCosts, i + 1, cost + j * toppingCosts[i], target, best);
        }
    }
};
