class Solution {
  public:
    int minDays(int n) {
        unordered_map<int, int> memo{};
        return dfs(n, memo);
    }

  private:
    int dfs(int n, unordered_map<int, int> &memo) {
        if (n <= 1) {
            return n;
        }
        if (memo.contains(n)) {
            return memo[n];
        }

        auto res =
            min((n % 2) + 1 + dfs(n / 2, memo), (n % 3) + 1 + dfs(n / 3, memo));

        return memo[n] = res;
    }
};
