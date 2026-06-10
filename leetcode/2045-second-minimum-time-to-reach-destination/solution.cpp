class Solution {
  public:
    int secondMinimum(int n, vector<vector<int>> &edges, int time, int change) {
        auto graph = vector<vector<int>>(n + 1);
        for (const auto &edge : edges) {
            const auto u = edge[0];
            const auto v = edge[1];

            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        auto dist = vector<pair<int, int>>(
            n + 1, {numeric_limits<int>::max(), numeric_limits<int>::max()});
        queue<int> q{{1}};
        dist[1] = {0, numeric_limits<int>::max()};

        for (int step = 0; !q.empty(); ++step) {
            for (int sz = q.size(); sz > 0; --sz) {
                const auto u = q.front();
                q.pop();

                for (const auto v : graph[u]) {
                    if (dist[v].first == numeric_limits<int>::max()) {
                        dist[v].first = step + 1;
                        q.push(v);
                    } else if (step + 1 > dist[v].first &&
                               step + 1 < dist[v].second) {
                        dist[v].second = step + 1;
                        q.push(v);
                    }
                }
            }
        }

        const auto secondMinEdges = dist[n].second;
        int res = 0;
        for (int i = 0; i < secondMinEdges; ++i) {
            const bool isGreen = (res / change) % 2 == 0;
            if (!isGreen) {
                res += change - (res % change);
            }
            res += time;
        }

        return res;
    }
};
