class Solution {
public:
    int findMin(vector<int>& nums) {
        int l {}, r {static_cast<int>(nums.size() - 1)}, minVal {nums[0]};

        while (l <= r) {
            if (nums[l] < nums[r]) {
                minVal = min(minVal, nums[l]);
                break;
            }
            int m = l + (r - l) / 2;
            minVal = min(minVal, nums[m]);

            if (nums[m] < nums[r]) {
                r = m - 1;
            } else {
                l = m + 1;
            }
        }

        return minVal;
    }
};
