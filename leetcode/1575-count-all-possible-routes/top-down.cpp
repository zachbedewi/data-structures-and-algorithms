class Solution {
public:
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        const int n = locations.size();
        vector<vector<int>> memo(n, vector<int>(fuel + 1, -1));
        return dfs(locations, memo, start, finish, fuel);
    }

private:
    static constexpr int MOD = 1'000'000'007;

    int dfs(
        const vector<int>& locations,
        vector<vector<int>>& memo,
        int current,
        int finish,
        int remainingFuel
    ) {
        if (remainingFuel < 0) {
            return 0;
        }
        if (memo[current][remainingFuel] != -1) {
            return memo[current][remainingFuel];
        }

        int res = current == finish ? 1 : 0;
        for (int next = 0; next < locations.size(); ++next) {
            const int cost = abs(locations[next] - locations[current]);
            if (next != current && remainingFuel >= cost) {
                res = (res + dfs(locations, memo, next, finish, remainingFuel - cost)) % MOD;
            }
        }
        return memo[current][remainingFuel] = res;
    }
};
