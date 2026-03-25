class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        const int n = colors.length();
        vector<vector<int>> graph(n);
        vector<int> inDegree(graph.size(), 0);
        for (const auto& edge : edges) {
            const int u = edge[0];
            const int v = edge[1];
            graph[u].push_back(v);
            ++inDegree[v];
        }

        queue<int> q;
        for (int i = 0; i < inDegree.size(); ++i) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        vector<vector<int>> count(n, vector<int>(26));
        int processed = 0;
        int res = 0;
        while (!q.empty()) {
            const auto out = q.front();
            q.pop();
            ++processed;
            res = max(res, ++count[out][colors[out] - 'a']);
            for (const auto& in : graph[out]) {
                for (int i = 0; i < 26; ++i) {
                    count[in][i] = max(count[in][i], count[out][i]);
                }
                if (--inDegree[in] == 0) {
                    q.push(in);
                };
            }
        }

        return processed == n ? res : -1;
    }
};
