class Solution {
public:
    auto longestCycle(vector<int>& edges) -> int {
        auto const n = edges.size();
        std::vector<int> visited(edges.size(), -1);
        auto time{0};
        auto res{-1};

        for (auto i : std::views::iota(0uz, n)) {
            if (visited[i] != -1) {
                continue;
            }

            auto start{time};
            auto x{i};
            while (x != -1 && visited[x] == -1) {
                visited[x] = time++;
                x = edges[x];
            }

            if (x != -1 && visited[x] >= start) {
                res = std::max(res, time - visited[x]);
            }
        }

        return res;
    }
};
