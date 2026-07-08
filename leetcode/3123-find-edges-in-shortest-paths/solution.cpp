class Solution {
  public:
    vector<bool> findAnswer(int n, vector<vector<int>> &edges) {
        vector<vector<pair<int, int>>> graph(n);
        for (const auto &edge : edges) {
            graph[edge[0]].emplace_back(edge[1], edge[2]);
            graph[edge[1]].emplace_back(edge[0], edge[2]);
        }

        const auto dist1 = djikstra(graph, 0);
        const auto dist2 = djikstra(graph, n - 1);

        const auto shortest = dist1[n - 1];
        vector<bool> res;

        for (const auto &edge : edges) {
            const auto u = edge[0];
            const auto v = edge[1];
            const auto w = edge[2];

            bool isIncluded = false;
            if (dist1[u] != numeric_limits<int>::max() &&
                dist2[v] != numeric_limits<int>::max() &&
                dist1[u] + w + dist2[v] == shortest) {
                isIncluded = true;
            }
            if (dist1[v] != numeric_limits<int>::max() &&
                dist2[u] != numeric_limits<int>::max() &&
                dist1[v] + w + dist2[u] == shortest) {
                isIncluded = true;
            }
            res.push_back(isIncluded);
        }

        return res;
    }

  private:
    vector<int> djikstra(const vector<vector<pair<int, int>>> graph,
                         int source) {
        vector<int> dist(graph.size(), numeric_limits<int>::max());
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>>
            minHeap;
        minHeap.emplace(0, source);
        dist[source] = 0;

        while (!minHeap.empty()) {
            const auto [weight, u] = minHeap.top();
            minHeap.pop();

            if (weight > dist[u]) {
                continue;
            }

            for (const auto [v, w] : graph[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    minHeap.emplace(dist[v], v);
                }
            }
        }

        return dist;
    }
};
