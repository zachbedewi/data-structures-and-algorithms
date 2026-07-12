class Solution {
  public:
    int countCompleteComponents(int n, vector<vector<int>> &edges) {
        vector<vector<int>> graph(n);
        for (auto const &edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        int res = 0;
        unordered_set<int> visited;
        for (int i = 0; i < n; ++i) {
            if (visited.contains(i))
                continue;
            vector<int> component(2, 0);
            dfs(graph, visited, component, i);

            if (component[0] * (component[0] - 1) / 2 == component[1] / 2) {
                ++res;
            }
        }

        return res;
    }

  private:
    void dfs(vector<vector<int>> const &graph, unordered_set<int> &visited,
             vector<int> &component, int u) {
        ++component[0];
        component[1] += graph[u].size();

        visited.insert(u);

        for (auto const &v : graph[u]) {
            if (!visited.contains(v)) {
                dfs(graph, visited, component, v);
            }
        }
    }
};
