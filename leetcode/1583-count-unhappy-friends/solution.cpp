class Solution {
public:
    int unhappyFriends(int n, vector<vector<int>>& preferences, vector<vector<int>>& pairs) {
        vector<int> pairMap(n, 0);
        for (const auto& pair : pairs) {
            pairMap[pair[0]] = pair[1];
            pairMap[pair[1]] = pair[0];
        }

        vector<unordered_map<int, int>> positions(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n - 1; ++j) {
                positions[i][preferences[i][j]] = j;
            }
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (const int j : preferences[i]) {
                if (positions[i][pairMap[i]] > positions[i][j] 
                    && positions[j][pairMap[j]] > positions[j][i]) {
                        ++ans;
                        break;
                    }
            }
        }
        return ans;
    }
};
