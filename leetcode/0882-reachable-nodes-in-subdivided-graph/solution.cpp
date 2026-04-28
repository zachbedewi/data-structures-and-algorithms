class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int maxMoves, int n) {
        vector<vector<pair<int, int>>> graph(n);

        for (const auto& edge : edges) {
            const int u = edge[0];
            const int v = edge[1];
            const int count = edge[2];
            graph[u].emplace_back(v, count);
            graph[v].emplace_back(u, count);
        }

        const vector<int> dist = dijkstra(graph, 0, maxMoves);
        const int reachableNodes = ranges::count_if(dist, [&](int d) { return d <= maxMoves; });

        int reachableSubNodes = 0;
        for (const auto& edge : edges) {
            const int u = edge[0];
            const int v = edge[1];
            const int count = edge[2];

            int a = dist[u] > maxMoves ? 0 : min(maxMoves - dist[u], count);
            int b = dist[v] > maxMoves ? 0 : min(maxMoves - dist[v], count);
            reachableSubNodes += min(a + b, count);
        }

        return reachableNodes + reachableSubNodes;
    }

private:
    vector<int> dijkstra(const vector<vector<pair<int, int>>> graph, int source, int maxMoves) {
        vector<int> dist(graph.size(), numeric_limits<int>::max());
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;

        dist[source] = 0;
        minHeap.emplace(dist[source], source);

        while (!minHeap.empty()) {
            const auto [d, u] = minHeap.top();
            minHeap.pop();

            if (d >= maxMoves) {
                continue;
            }
            if (d > dist[u]) {
                continue;
            }

            for (const auto& [v, w] : graph[u]) {
                if (d + w + 1 < dist[v]) {
                    dist[v] = d + w + 1;
                    minHeap.emplace(dist[v], v);
                }
            }
        }

        return dist;
    }
};
