class Solution {
public:
    int maximumScore(vector<int>& scores, vector<vector<int>>& edges) {
        const int n = scores.size();
        vector<vector<int>> graph(n);

        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        for (auto& node : graph) {
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>>
                pq;
            for (const int neighbor : node) {
                const int score = scores[neighbor];
                pq.push({score, neighbor});
                if (pq.size() > 3) {
                    pq.pop();
                }
            }

            node.resize(pq.size());
            for (int sz = node.size() - 1; sz >= 0; --sz) {
                node[sz] = pq.top().second;
                pq.pop();
            }
        }

        int res = -1;
        for (const vector<int>& edge : edges) {
            const int u = edge[0];
            const int v = edge[1];
            const int baseScore = scores[u] + scores[v];
            for (const auto& a : graph[u]) {
                for (const auto& b : graph[v]) {
                    if (a != b && a != v && b != u) {
                        res = max(res, scores[a] + baseScore + scores[b]);
                    }
                }
            }
        }

        return res;
    }
};
