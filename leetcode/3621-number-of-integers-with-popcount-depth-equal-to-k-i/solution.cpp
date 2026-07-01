class Solution {
  public:
    long long popcountDepth(long long n, int k) {
        if (k == 0)
            return 1;
        const auto bits = bit_width(static_cast<uint64_t>(n));
        auto depth = computePopcountDepth(bits);
        auto memo = vector(bits, vector<long long>(bits, -1));
        long long res = solve(n, k, memo, depth, 0, 1, 0);
        if (k == 1)
            --res;
        return res;
    }

  private:
    vector<int> computePopcountDepth(int bits) {
        auto depth = vector<int>(bits + 1, 0);
        for (int i = 2; i <= bits; ++i) {
            depth[i] = 1 + depth[__builtin_popcount(i)];
        }
        return depth;
    }

    long long solve(long long n, int k, vector<vector<long long>> &memo,
                    const vector<int> &depth, int pos, int tight,
                    int popcount) {
        const auto bits = bit_width(static_cast<uint64_t>(n));
        if (pos == bits) {
            return popcount >= 1 && depth[popcount] == k - 1;
        }
        if (!tight && memo[pos][popcount] != -1) {
            return memo[pos][popcount];
        }

        int bit = (n >> (bits - 1 - pos)) & 1LL;
        int limit = tight ? bit : 1;

        long long res = 0;
        for (int d = 0; d <= limit; ++d) {
            res += solve(n, k, memo, depth, pos + 1, tight && (d == bit),
                         popcount + d);
        }

        if (!tight) {
            memo[pos][popcount] = res;
        }
        return res;
    }
};
