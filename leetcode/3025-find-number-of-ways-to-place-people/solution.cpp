class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points) {
        const int n = points.size();
        ranges::sort(points, [](const auto& a, const auto& b) {
            return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
        });

        int count = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1, maxY = INT_MIN; j < n; ++j) {
                if (points[i][1] >= points[j][1] && points[j][1] > maxY) {
                    ++count;
                    maxY = points[j][1];
                }
            }
        }
        return count;
    }
};
