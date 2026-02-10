class Solution {
public:
    int specialPerm(vector<int>& nums) {
        const int n = nums.size();
        const int maxMask = 1 << n;
        vector<vector<int>> mem(n, vector<int>(maxMask, -1));
        return specialPerm(nums, maxMask, 0, 0, mem);
    }

private:

    static constexpr int MOD = 1'000'000'007;

    int specialPerm(
        const vector<int>& nums,
        const int maxMask,
        int prev,
        int mask,
        vector<vector<int>>& mem
    ) {
        if (mask == maxMask - 1) {
            return 1;
        }
        if (mem[prev][mask] != -1) {
            return mem[prev][mask];
        }

        int res = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if ((mask & (1 << i)) != 0) {
                continue;
            }

            if (mask == 0 || nums[i] % nums[prev] == 0 || nums[prev] % nums[i] == 0) {
                res += specialPerm(nums, maxMask, i, mask | (1 << i), mem);
                res %= MOD;
            }
        }

        return mem[prev][mask] = res;
    }
};
