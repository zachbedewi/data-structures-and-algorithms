class Solution {
public:
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        const int n = nums1.size();
        const int minEnd = min(nums1[n - 1], nums2[n - 1]);
        const int maxEnd = max(nums1[n - 1], nums2[n - 1]);

        int endSwappedCount = 0;
        int endNotSwappedCount = 0;
        for (int i = 0; i < n; ++i) {
            const int num1 = nums1[i];
            const int num2 = nums2[i];
            if (max(num1, num2) > maxEnd) {
                return -1;
            }
            if (min(num1, num2) > minEnd) {
                return -1;
            }
            if (num1 > nums1[n - 1] || num2 > nums2[n - 1]) {
                ++endNotSwappedCount;
            }
            if (num1 > nums2[n - 1] || num2 > nums1[n - 1]) {
                ++endSwappedCount;
            }
        }
        return min(endSwappedCount, endNotSwappedCount);
    }
};
