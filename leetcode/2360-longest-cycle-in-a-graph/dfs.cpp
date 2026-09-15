class Solution {
public:
    int longestCycle(vector<int>& edges) {
        std::vector<bool> visited(edges.size(), false);

        for (auto i : std::views::iota(0, static_cast<int>(edges.size()))) {
            if (visited[i]) {
                continue;
            }

            std::vector<int> path;
            dfs(edges, visited, i, path);
        }

        return maxLength;
    }

private:
    auto dfs(std::vector<int> const& edges, std::vector<bool>& visited, int curr, std::vector<int>& path) -> void {
        if (curr == -1) {
            return;
        }

        if (visited[curr]) {
            auto start{-1};

            for (auto [i, node] : std::views::enumerate(path)) {
                if (curr == node) {
                    start = i;
                    break;
                }
            }

            if (start == -1) {
                return;
            }

            maxLength = std::max(maxLength, static_cast<int>(path.size()) - start);
            return;
        }

        visited[curr] = true;
        path.push_back(curr);
        dfs(edges, visited, edges[curr], path);
    }

    int maxLength{-1};
};
