class Solution {
  public:
    int divisibleGame(vector<int> &nums) {
        auto const n = nums.size();

        unordered_set<int> candidates{2};

        for (auto const num : nums) {
            for (int d = 2; d * d <= num; ++d) {
                if (num % d == 0) {
                    candidates.insert(d);
                    candidates.insert(num / d);
                }
            }
            if (num > 1) {
                candidates.insert(num);
            }
        }

        auto bestScore = [&](int k) -> long long {
            long long res = numeric_limits<long long>::min();
            long long curr = numeric_limits<long long>::min();

            for (auto const &num : nums) {
                long long val = (num % k == 0) ? num : -num;
                curr = curr == numeric_limits<long long>::min()
                           ? val
                           : max(val, curr + val);
                res = max(res, curr);
            }

            return res;
        };

        long long bestK = 2;
        long long maxScore = numeric_limits<long long>::min();
        for (auto const k : candidates) {
            if (long long score = bestScore(k);
                score > maxScore || (score == maxScore && k < bestK)) {
                bestK = k;
                maxScore = score;
            }
        }

        auto posmod = [](long long x, long long m) {
            return ((x % m) + m) % m;
        };
        return posmod(posmod(maxScore, MOD) * bestK, MOD);
    }

  private:
    static constexpr int MOD = 1e9 + 7;
};
