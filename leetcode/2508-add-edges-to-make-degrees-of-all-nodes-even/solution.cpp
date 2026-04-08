class Solution {
public:
    bool isPossible(int n, vector<vector<int>>& edges) {
        vector<unordered_set<int>> graph(n + 1);
        for (const auto& edge : edges) {
            const int u = edge[0];
            const int v = edge[1];
            graph[u].insert(v);
            graph[v].insert(u);
        }

        vector<int> oddDegreeNodes;
        for (int i = 1; i <= n; ++i) {
            if (graph[i].size() % 2 != 0) {
                oddDegreeNodes.push_back(i);
            }
        }

        if (oddDegreeNodes.size() == 2) {
            const int first = oddDegreeNodes[0];
            const int second = oddDegreeNodes[1];
            for (int i = 1; i <= n; ++i) {
                if (graph[first].count(i) == 0 && graph[second].count(i) == 0) {
                    return true;
                }
            }
        }

        if (oddDegreeNodes.size() == 4) {
            const int first = oddDegreeNodes[0];
            const int second = oddDegreeNodes[1];
            const int third = oddDegreeNodes[2];
            const int fourth = oddDegreeNodes[3];
            return (graph[first].count(second) == 0 && graph[third].count(fourth) == 0)
                || (graph[first].count(third) == 0 && graph[second].count(fourth) == 0)
                || (graph[first].count(fourth) == 0 && graph[second].count(third) == 0);
        }

        return oddDegreeNodes.size() == 0;
    }
};
