class Solution {
public:
    int maxIncreasingSubarrays(vector<int>& nums) {
        int maxK = 0;
        int previousSubarrayLength = 0;
        int currentSubarrayLength = 1;

        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i - 1] < nums[i]) {
                ++currentSubarrayLength;
            } else {
                previousSubarrayLength = currentSubarrayLength;
                currentSubarrayLength = 1;
            }
            maxK = max(
                maxK,
                max(currentSubarrayLength / 2, min(previousSubarrayLength, currentSubarrayLength)));
        }

        return maxK;
    }
};
