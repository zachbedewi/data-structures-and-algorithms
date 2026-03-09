class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        vector<int> bitCount(32, 0);
        for (const auto num : nums) {
            for (int b = 0; b < 32; ++b) {
                if (num & (1 << b)) {
                    ++bitCount[b];
                }
            }
        }

        int res = 0;
        for (int i = 0; i < k; ++i) {
            long long n = 0;
            for (int b = 0; b < 32; ++b) {
                if (--bitCount[b] >= 0) {
                    n += (1 << b);
                }
            }
            res = (res + n * n) % MOD;
        }

        return res;
    }

private:
    static constexpr int MOD = 1'000'000'007;
};
