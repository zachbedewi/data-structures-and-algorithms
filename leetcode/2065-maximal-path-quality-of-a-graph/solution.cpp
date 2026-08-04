class Solution {
  public:
    int maximalPathQuality(vector<int> &values, vector<vector<int>> &edges,
                           int maxTime) {
        auto const n{values.size()};
        auto res{values[0]};
        vector<vector<pair<int, int>>> graph(n);

        for (auto const &edge : edges) {
            graph[edge[0]].emplace_back(edge[1], edge[2]);
            graph[edge[1]].emplace_back(edge[0], edge[2]);
        }

        vector<int> visited(n, 0);
        dfs(graph, values, visited, 0, 0, maxTime, 0, res);
        return res;
    }

  private:
    void dfs(vector<vector<pair<int, int>>> const &graph,
             vector<int> const &values, vector<int> &visited, int node,
             int time, int maxTime, int score, int &res) {
        if (time > maxTime) {
            return;
        }

        if (visited[node] == 0) {
            score += values[node];
        }

        ++visited[node];

        if (node == 0) {
            res = max(res, score);
        }

        for (auto const &[u, inc] : graph[node]) {
            dfs(graph, values, visited, u, time + inc, maxTime, score, res);
        }

        --visited[node];
    }
};
