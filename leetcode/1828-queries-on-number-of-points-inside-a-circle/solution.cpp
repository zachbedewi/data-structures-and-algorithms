class Solution {
public:
    vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries) {
        std::ranges::sort(points, {}, [](auto const& a) {
            return a[0];
        });

        auto const countInCircle = [&](auto const& q) {
            auto const x = q[0];
            auto const y = q[1];
            auto const r = q[2];
            auto const r2 = r * r;

            auto const lo = std::ranges::lower_bound(points, x - r, {}, [](auto const& p) { return p[0]; });
            auto const window = std::ranges::subrange(lo, points.end())
                                | std::views::take_while([x, r](auto const& p) { return p[0] <= x + r; });

            return static_cast<int>(std::ranges::count_if(window, [x, y, r2](auto const& p) {
                auto const dx = x - p[0];
                auto const dy = y - p[1];
                return dx * dx + dy * dy <= r2;
            }));
        };

        return queries | std::views::transform(countInCircle) | std::ranges::to<std::vector>();
    }
};
