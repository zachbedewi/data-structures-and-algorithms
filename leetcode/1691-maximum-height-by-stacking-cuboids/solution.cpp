class Solution {
  public:
    int maxHeight(vector<vector<int>> &cuboids) {
        auto const n{cuboids.size()};
        std::ranges::for_each(
            cuboids, [](std::vector<int> &a) { std::ranges::sort(a); });
        std::ranges::sort(cuboids);
        std::vector<int> dp(n);

        auto res{0};
        for (auto j : std::views::iota(0uz, n)) {
            dp[j] = cuboids[j].back();
            for (auto i : std::views::iota(0uz, j)) {
                if (cuboids[i][0] <= cuboids[j][0] &&
                    cuboids[i][1] <= cuboids[j][1] &&
                    cuboids[i][2] <= cuboids[j][2]) {
                    dp[j] = std::max(dp[j], dp[i] + cuboids[j].back());
                }
            }
            res = std::max(res, dp[j]);
        }
        return res;
    }
};
