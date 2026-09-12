class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        auto const n{static_cast<int>(grid.size())};
        auto const m{static_cast<int>(grid[0].size())};

        auto res{0};
        std::unordered_map<int, int> area{};
        auto islandId{2};
        for (auto r : std::views::iota(0, n)) {
            for (auto c : std::views::iota(0, m)) {
                if (grid[r][c] == 1) {
                    area[islandId] = dfs(grid, r, c, islandId);
                    res = std::max(res, area[islandId++]);
                }
            }
        }

        for (auto r : std::views::iota(0, n)) {
            for (auto c : std::views::iota(0, m)) {
                if (grid[r][c] != 0) {
                    continue;
                }
                
                std::unordered_set<int> seen{};
                auto currArea{1};
                for (auto const& [dr, dc] : kDirections) {
                    auto const newR = r + dr;
                    auto const newC = c + dc;
                    if (newR < 0 || newR >= n || newC < 0 || newC >= m) {
                        continue;
                    }

                    auto id = grid[newR][newC];
                    if (id > 1 && !seen.contains(id)) {
                        currArea += area[id];
                        seen.insert(id);
                    }
                }

                res = std::max(res, currArea);
            }
        }

        return res;
    }

private:

    static constexpr std::array<std::pair<int, int>, 4> kDirections = {{
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1}
    }};

    auto dfs(std::vector<std::vector<int>>& grid, int r, int c, int islandId) -> int {
        if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size() || grid[r][c] != 1) {
            return 0;
        }

        grid[r][c] = islandId;
        auto area{0};
        for (auto const& [dr, dc] : kDirections) {
            auto newR = r + dr;
            auto newC = c + dc;
            area += dfs(grid, newR, newC, islandId);
        }
        return 1 + area;
    }
};
