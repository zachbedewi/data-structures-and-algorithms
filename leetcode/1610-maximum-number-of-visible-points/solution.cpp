class Solution {
  public:
    int visiblePoints(vector<vector<int>> &points, int angle,
                      vector<int> &location) {
        auto const n = points.size();

        auto shared{0};
        vector<double> angles;
        for (auto const &point : points) {
            auto const xDiff = point[0] - location[0];
            auto const yDiff = point[1] - location[1];
            if (xDiff == 0 && yDiff == 0) {
                ++shared;
            } else {
                angles.emplace_back(getAngle(xDiff, yDiff));
            }
        }

        ranges::sort(angles);
        auto const numAngles{angles.size()};
        for (auto i{0uz}; i < numAngles; ++i) {
            angles.push_back(angles[i] + 360);
        }

        auto res{0};
        for (auto i{0}, j{0}; i < angles.size(); ++i) {
            while (j < angles.size() &&
                   (angles[j] - angles[i] <=
                    angle + std::numeric_limits<double>::epsilon())) {
                ++j;
            }
            res = max(res, j - i);
        }
        return res + shared;
    }

  private:
    double getAngle(int x, int y) {
        auto a = atan2(y, x) * 180 / std::numbers::pi;
        if (a < 0) {
            a += 360;
        }
        return a;
    }
};
