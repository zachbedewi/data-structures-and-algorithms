class Solution {
public:
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            const int u = edge[0];
            const int v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        
        vector<int> ans(n, 0);
        vector<int> frequencyMap(26, 0);
        dfs(0, 0, graph, labels, ans, frequencyMap);

        return ans;
    }

private:
    void dfs(
        int node,
        int prevNode,
        const vector<vector<int>>& graph,
        const string& labels,
        vector<int>& ans,
        vector<int>& frequencyMap
    ) {
        int prevCount = frequencyMap[labels[node] - 'a'];

        ++frequencyMap[labels[node] - 'a'];

        for (const int nextNode : graph[node]) {
            if (prevNode == nextNode) {
                continue;
            }
            dfs(nextNode, node, graph, labels, ans, frequencyMap);
        }

        ans[node] = frequencyMap[labels[node] - 'a'] - prevCount;
    }
};
