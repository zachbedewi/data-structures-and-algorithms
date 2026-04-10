class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        int maxIdx = -1;
        int minIdx = -1;
        int lastInvalidIdx = -1;

        long long res = 0;
        for (int i = 0; i < nums.size(); ++i) {
            const int num = nums[i];
            if (num < minK || num > maxK) {
                lastInvalidIdx = i;
            }
            if (num == maxK) {
                maxIdx = i;
            }
            if (num == minK) {
                minIdx = i;
            }
            res += max(0, min(maxIdx, minIdx) - lastInvalidIdx);
        }
        return res;
    }
};
