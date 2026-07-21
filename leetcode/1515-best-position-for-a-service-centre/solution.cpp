class Solution {
  public:
    double getMinDistSum(vector<vector<int>> &positions) {
        auto res{numeric_limits<double>::max()};
        vector<double> candidate(2, 0);

        double step{100.0};
        double epsilon{1e-6};

        while (step > epsilon) {
            bool found = false;
            for (auto &dir : directions) {
                vector<double> nextCandidate = {candidate[0] + step * dir[0],
                                                candidate[1] + step * dir[1]};
                auto newDist = cumulativeDist(positions, nextCandidate);
                if (newDist < res) {
                    res = newDist;
                    candidate = nextCandidate;
                    found = true;
                    break;
                }
            }
            if (!found) {
                step /= 2;
            }
        }

        return res;
    }

  private:
    static constexpr array<array<int, 2>, 4> directions = {
        {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};

    double dist(const vector<int> &a, const vector<double> &b) {
        return sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2));
    }

    double cumulativeDist(const vector<vector<int>> &points,
                          const vector<double> &candidate) {
        auto res{0.0};
        for (auto const &point : points) {
            res += dist(point, candidate);
        }
        return res;
    }
};
