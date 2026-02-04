class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        const int n = board.size();
        queue<int> q {{1}};
        vector<bool> visited(n * n + 1);
        visited[1] = true;

        for (int step = 1; !q.empty(); ++step) {
            for (int sz = q.size(); sz > 0; --sz) {
                const int curr = q.front();
                q.pop();

                for (int next = curr + 1; next <= min(curr + 6, n * n); ++next) {
                    const int r = (n - 1) - ((next - 1) / n);
                    int c = (next - 1) % n;
                    if ((n - r) % 2 == 0) {
                        c = n - 1 - c;
                    }
                    const int dest = board[r][c] > 0 ? board[r][c] : next;

                    if (dest == n * n) {
                        return step;
                    }
                    if (visited[dest]) {
                        continue;
                    }
                    q.push(dest);
                    visited[dest] = true;
                }
            }
        }

        return -1;
    }
};
