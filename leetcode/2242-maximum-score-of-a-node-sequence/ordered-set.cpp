class Solution {
public:
    int maximumScore(vector<int>& scores, vector<vector<int>>& edges) {
        vector<set<pair<int, int>>> graph(scores.size());

        for (const auto& edge : edges) {
            const int u = edge[0];
            const int v = edge[1];
            graph[u].emplace(scores[v], v);
            graph[v].emplace(scores[u], u);
            if (graph[u].size() > 3) {
                // Remove the smallest element from the set
                graph[u].erase(graph[u].begin());
            }
            if (graph[v].size() > 3) {
                // Remove the smallest element from the set
                graph[v].erase(graph[v].begin());
            }
        }

        int res = -1;
        for (const vector<int>& edge : edges) {
            const int u = edge[0];
            const int v = edge[1];
            const int baseScore = scores[u] + scores[v];
            for (const auto& [scoreA, a] : graph[u]) {
                for (const auto& [scoreB, b] : graph[v]) {
                    if (a != b && a != v && b != u) {
                        res = max(res, scoreA + baseScore + scoreB);
                    }
                }
            }
        }

        return res;
    }
};
