class Solution {
  public:
    int preimageSizeFZF(int k) { return search(k) - search(k - 1); }

  private:
    auto numTrailingZeros(long x) -> long {
        auto res{0L};

        for (; x > 0; x /= 5) {
            res += x / 5;
        }

        return res;
    }

    auto search(int k) -> int {
        auto l{0L};
        auto r{5L * (static_cast<long>(k) + 1)};

        while (l < r) {
            auto m{l + (r - l) / 2};
            auto opt{numTrailingZeros(m)};

            if (opt <= k) {
                l = m + 1;
            } else {
                r = m;
            }
        }

        return l;
    }
};
