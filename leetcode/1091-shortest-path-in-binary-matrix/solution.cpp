class Solution {
  public:
    int shortestPathBinaryMatrix(vector<vector<int>> &grid) {
        auto const n = grid.size();
        if (grid[0][0] != 0 || grid[n - 1][n - 1] != 0) {
            return -1;
        }

        std::queue<std::pair<int, int>> q{{{0, 0}}};
        grid[0][0] = 1;

        for (auto length{1}; !q.empty(); ++length) {
            for (auto sz{q.size()}; sz > 0; --sz) {
                auto const [currX, currY] = q.front();
                q.pop();

                if (currX == n - 1 && currY == n - 1) {
                    return length;
                }

                for (auto const [dx, dy] : DIRECTIONS) {
                    auto newX = currX + dx;
                    auto newY = currY + dy;
                    if (newX < 0 || newX > n - 1 || newY < 0 || newY > n - 1 ||
                        grid[newX][newY] != 0) {
                        continue;
                    }
                    q.emplace(newX, newY);
                    grid[newX][newY] = 1;
                }
            }
        }

        return -1;
    }

  private:
    static constexpr array<std::pair<int, int>, 8> DIRECTIONS = {
        {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1}}};
};
