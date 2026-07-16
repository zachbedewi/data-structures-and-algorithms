class Solution {
  public:
    int numBusesToDestination(vector<vector<int>> &routes, int source,
                              int target) {
        auto const n = routes.size();
        unordered_map<int, vector<int>> graph;
        for (auto const &[id, route] : routes | views::enumerate) {
            for (int i = 0; i < route.size(); ++i) {
                graph[route[i]].push_back(id);
            }
        }

        queue<pair<int, int>> q;
        unordered_set<int> visited;

        q.push({source, 0});
        visited.insert(source);

        while (!q.empty()) {
            auto const [stop, route] = q.front();
            q.pop();

            if (stop == target) {
                return route;
            }
            for (auto const &nextRoute : graph[stop]) {
                for (auto const &nextStop : routes[nextRoute]) {
                    if (visited.contains(nextStop)) {
                        continue;
                    }

                    q.push({nextStop, route + 1});
                    visited.insert(nextStop);
                }
                routes[nextRoute].clear();
            }
        }

        return -1;
    }
};
