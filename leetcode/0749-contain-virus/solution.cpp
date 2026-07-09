struct Cluster {
    set<pair<int, int>> contaminated;
    set<pair<int, int>> uncontaminated;
    int walls = 0;
};

class Solution {
  public:
    int containVirus(vector<vector<int>> &isInfected) {
        const auto n = isInfected.size();
        const auto m = isInfected[0].size();
        auto res = 0;
        while (true) {
            auto visited{vector(n, vector<bool>(m, false))};
            const auto comp = [](const Cluster &a, const Cluster &b) {
                return a.uncontaminated.size() < b.uncontaminated.size();
            };
            priority_queue<Cluster, vector<Cluster>, decltype(comp)> pq(comp);

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (!visited[i][j] && isInfected[i][j] == 1) {
                        Cluster c;
                        dfs(isInfected, visited, i, j, c);
                        pq.push(c);
                    }
                }
            }

            if (pq.size() == 0)
                break;

            auto c = pq.top();
            pq.pop();

            for (const auto [x, y] : c.contaminated) {
                isInfected[x][y] = -1;
            }
            res += c.walls;

            while (!pq.empty()) {
                auto c = pq.top();
                pq.pop();
                for (const auto [x, y] : c.uncontaminated) {
                    isInfected[x][y] = 1;
                }
            }
        }

        return res;
    }

  private:
    void dfs(vector<vector<int>> &grid, vector<vector<bool>> &visited, int i,
             int j, Cluster &cluster) {
        if (i == grid.size() || i < 0 || j == grid[0].size() || j < 0 ||
            visited[i][j] || grid[i][j] == -1) {
            return;
        }

        if (grid[i][j] == 0) {
            ++cluster.walls;
            cluster.uncontaminated.insert({i, j});
            return;
        }

        cluster.contaminated.insert({i, j});
        visited[i][j] = true;

        dfs(grid, visited, i + 1, j, cluster);
        dfs(grid, visited, i - 1, j, cluster);
        dfs(grid, visited, i, j + 1, cluster);
        dfs(grid, visited, i, j - 1, cluster);
    }
};
