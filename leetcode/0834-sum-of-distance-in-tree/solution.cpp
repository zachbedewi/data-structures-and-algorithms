class Solution {
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            const int u = edge[0];
            const int v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        vector<int> count(n, 0);
        vector<int> res(n, 0);

        postOrderDfs(graph, -1, 0, count, res);
        preOrderDfs(graph, -1, 0, count, res);
        return res;
    }

private:
    int postOrderDfs(
        const vector<vector<int>>& graph,
        int parent,
        int curr,
        vector<int>& count,
        vector<int>& res
    ) {
        int localCount = 1;
        for (const auto& neighbor : graph[curr]) {
            if (neighbor != parent) {
                localCount += postOrderDfs(graph, curr, neighbor, count, res);
            }
        }

        if (curr != 0) {
            res[0] += localCount;
        }
        return count[curr] = localCount;
    }

    void preOrderDfs(
        const vector<vector<int>>& graph,
        int parent,
        int curr,
        vector<int>& count,
        vector<int>& res
    ) {
        if (curr != 0) {
            res[curr] = res[parent] - count[curr] + (graph.size() - count[curr]);
        }

        for (const auto& neighbor : graph[curr]) {
            if (neighbor != parent) {
                preOrderDfs(graph, curr, neighbor, count, res);
            }
        }
    }
};
