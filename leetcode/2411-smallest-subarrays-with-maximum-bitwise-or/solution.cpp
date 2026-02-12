class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        const int n = nums.size();

        vector<int> res(n, 1);
        vector<int> closest(30, -1);

        for (int i = n - 1; i >= 0; --i) {
            for (int b = 0; b < 30; ++b) {
                if (nums[i] & (1 << b)) {
                    closest[b] = i;
                }
                res[i] = max(res[i], closest[b] - i + 1);
            }
        }

        return res;
    }
};
