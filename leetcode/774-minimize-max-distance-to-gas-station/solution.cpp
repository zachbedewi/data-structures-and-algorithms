class Solution {
  public:
    double minmaxGasDist(vector<int> &stations, int k) {
        double l = 0;
        double r = stations.back() - stations.front();
        while (l + 1e-6 < r) {
            double m = (l + r) / 2;
            if (check(stations, k, m)) {
                r = m;
            } else {
                l = m;
            }
        }
        return l;
    }

  private:
    auto check(const vector<int> &stations, int k, double penalty) -> bool {
        auto needed = 0;
        for (auto i{1uz}; i < stations.size(); ++i) {
            needed += ceil((stations[i] - stations[i - 1]) / penalty) - 1;
        }
        return needed <= k;
    }
};
