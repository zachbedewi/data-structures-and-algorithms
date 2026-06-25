class Solution {
  public:
    vector<int> minEdgeReversals(int n, vector<vector<int>> &edges) {
        vector<vector<pair<int, int>>> graph(n);
        for (const auto &e : edges) {
            const auto u = e[0];
            const auto v = e[1];
            graph[u].emplace_back(v, 0);
            graph[v].emplace_back(u, 1);
        }
        vector<int> res(n, 0);

        auto count = [&](auto &&self, int node, int parent) -> int {
            int total = 0;
            for (const auto &[next, cost] : graph[node]) {
                if (next == parent)
                    continue;
                total += cost + self(self, next, node);
            }
            return total;
        };
        res[0] = count(count, 0, -1);

        auto reroot = [&](auto &&self, int node, int parent) -> void {
            for (const auto &[next, cost] : graph[node]) {
                if (next == parent)
                    continue;
                res[next] = res[node] + (cost == 0 ? 1 : -1);
                self(self, next, node);
            }
        };
        reroot(reroot, 0, -1);

        return res;
    }
};
