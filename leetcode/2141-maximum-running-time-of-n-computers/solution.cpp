class Solution {
  public:
    long long maxRunTime(int n, vector<int> &batteries) {
        auto feasible = [&](long long const m) {
            auto total{0LL};
            for (auto const battery : batteries) {
                total += min(static_cast<long long>(battery), m);
            }
            return total >= n * m;
        };

        auto l{0LL};
        auto r{ranges::fold_left(batteries, 0LL, plus<>{}) / n};

        while (l < r) {
            auto m{l + (r - l + 1) / 2};
            if (feasible(m)) {
                l = m;
            } else {
                r = m - 1;
            }
        }

        return l;
    }
};
