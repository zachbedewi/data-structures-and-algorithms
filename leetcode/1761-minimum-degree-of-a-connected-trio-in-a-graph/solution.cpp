class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n + 1, vector<int>(n + 1));
        vector<int> degree(n + 1);
        for (const auto& edge : edges) {
            const int u = edge[0];
            const int v = edge[1];
            graph[u][v] = graph[v][u] = 1;
            ++degree[u];
            ++degree[v];
        }

        int ans = INT_MAX;
        for (int i = 0; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (graph[i][j] == 1) {
                    for (int k = j + 1; k <= n; ++k) {
                        if (graph[i][k] && graph[j][k]) {
                            ans = min(ans, degree[i] + degree[j] + degree[k] - 6);
                        }
                    }
                }
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }
};
