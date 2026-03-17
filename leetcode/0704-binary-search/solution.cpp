class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l {}, r {static_cast<int>(nums.size())}, mid {};

        while (l < r) {
            mid = l + (r - l)/2;
            if (nums[mid] >= target) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }

        return (l < nums.size() && nums[l] == target) ? l : -1;
    }
};
