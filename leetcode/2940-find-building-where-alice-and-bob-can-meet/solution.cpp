class Solution {
public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        const int n = heights.size();
        const int numQueries = queries.size();
        vector<vector<vector<int>>> minIndexToMaxHeight(n);
        vector<int> res(numQueries, -1);

        for (int i = 0; i < numQueries; ++i) {
            const int a = queries[i][0];
            const int b = queries[i][1];
            if (a < b && heights[a] < heights[b]) {
                res[i] = b;
            } else if (b < a && heights[b] < heights[a]) {
                res[i] = a;
            } else if (a == b) {
                res[i] = a;
            } else {
                minIndexToMaxHeight[max(a, b)].push_back({max(heights[a], heights[b]), i});
            }
        }

        priority_queue<vector<int>, vector<vector<int>>, greater<>> minQ;
        for (int i = 0; i < n; ++i) {
            while (!minQ.empty() && minQ.top()[0] < heights[i]) {
                const int query = minQ.top()[1];
                res[query] = i;
                minQ.pop();
            }
            for (auto& entry : minIndexToMaxHeight[i]) {
                minQ.push(entry);
            }
        }
        return res;
    }
};
