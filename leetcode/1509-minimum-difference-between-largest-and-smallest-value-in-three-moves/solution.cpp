class Solution {
public:
    int minDifference(vector<int>& nums) {
        if (nums.size() <= 4) {
            return 0;
        }
        
        ranges::sort(nums);
        const int k = nums.size() - 4;
        int ans = nums.back() - nums[0];
        for (int r = k; r < nums.size(); ++r) {
            const int l = r - k;
            ans = min(ans, nums[r] - nums[l]);
        }
        return ans;
    }
};
