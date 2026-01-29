class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        const string target = "123450";
        const vector<vector<int>> validMoves {{1, 3}, {0, 2, 4}, {1, 5}, {0, 4}, {1, 3, 5}, {2, 4}};

        string current = "";
        int startIndex = -1;
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                current += to_string(board[i][j]);
                if (board[i][j] == 0) {
                    startIndex = i * 3 + j;
                }
            }
        }

        unordered_set<string> visited;
        queue<pair<string, int>> q {{{current, startIndex}}};
        visited.insert(current);

        for (int count = 0; !q.empty(); ++count) {
            for (int sz = q.size(); sz > 0; --sz) {
                const auto [layout, currZeroIndex] = q.front();
                q.pop();

                if (layout == target) {
                    return count;
                }

                for (const auto& nextZeroIndex : validMoves[currZeroIndex]) {
                    string layoutCopy = layout;
                    swap(layoutCopy[currZeroIndex], layoutCopy[nextZeroIndex]);

                    if (visited.count(layoutCopy)) {
                        continue;
                    }

                    q.emplace(layoutCopy, nextZeroIndex);
                    visited.insert(layoutCopy);
                }
            }
        }

        return -1;
    }
};
