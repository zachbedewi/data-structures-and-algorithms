class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        const int n = graph.size();
        auto dp = vector(n, vector<bool>(1 << n, false));
        auto q {queue<pair<int, int>>{}};

        for (int i = 0; i < n; ++i) {
            dp[i][1 << i] = true;
            q.emplace(i, 1 << i);
        }

        const auto fullMask = (1 << n) - 1;
        for (int step = 0; !q.empty(); ++step) {
            for (auto sz = q.size(); sz > 0; --sz) {
                const auto [node, mask] = q.front();
                q.pop();

                if (mask == fullMask) {
                    return step;
                }

                for (const auto neighbor : graph[node]) {
                    const auto newMask = mask | (1 << neighbor);
                    if (dp[neighbor][newMask] == false) {
                        dp[neighbor][newMask] = true;
                        q.emplace(neighbor, newMask);
                    }
                }
            }
        }

        throw;
    }
};
