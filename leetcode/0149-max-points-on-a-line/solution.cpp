class Solution {
  public:
    int maxPoints(vector<vector<int>> &points) {
        int res = 1;
        unordered_map<double, int> slopeCount;
        for (const auto &p1 : points) {
            for (const auto &p2 : points) {
                if (p1 == p2) {
                    continue;
                }
                res = max(res, ++slopeCount[calcSlope(p1, p2)] + 1);
            }
            slopeCount.clear();
        }

        return res;
    }

  private:
    double calcSlope(const vector<int> &p1, const vector<int> &p2) {
        return p1[0] == p2[0] ? numeric_limits<double>::max()
                              : static_cast<double>(p2[1] - p1[1]) /
                                    static_cast<double>(p2[0] - p1[0]);
    }
};
