class Solution {
  public:
    int maximumRequests(int n, vector<vector<int>> &requests) {
        auto const requestCount = requests.size();

        int res = 0;
        for (int i = 0; i < (1 << requestCount); ++i) {
            vector<int> inDegree(n, 0);
            for (int j = 0; j < requestCount; ++j) {
                if (i & (1 << j)) {
                    --inDegree[requests[j][0]];
                    ++inDegree[requests[j][1]];
                }
            }
            if (all_of(inDegree.begin(), inDegree.end(),
                       [](int x) { return x == 0; })) {
                res = max(res, __builtin_popcount(i));
            }
        }

        return res;
    }
};
