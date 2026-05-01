class Solution {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        int swap = 1;
        int fix = 0;

        for (int i = 1; i < nums1.size(); ++i) {
            // don't swap at i - 1, don't swap at i
            // swap at i - 1, swap at i
            int noSwapPrevCurr = numeric_limits<int>::max();
            int swapPrevCurr = numeric_limits<int>::max();
            if (nums1[i - 1] < nums1[i] && nums2[i - 1] < nums2[i]) {
                noSwapPrevCurr = fix;
                swapPrevCurr = swap + 1;
            }
            // don't swap at i - 1, swap at i
            int noSwapPrevSwapCurr = numeric_limits<int>::max();
            int swapPrevNoSwapCurr = numeric_limits<int>::max();
            if (nums1[i - 1] < nums2[i] && nums2[i - 1] < nums1[i]) {
                noSwapPrevSwapCurr = fix + 1;
                swapPrevNoSwapCurr = swap;
            }
            swap = min(swapPrevCurr, noSwapPrevSwapCurr);
            fix = min(noSwapPrevCurr, swapPrevNoSwapCurr);
        }

        return min(swap, fix);
    }
};
