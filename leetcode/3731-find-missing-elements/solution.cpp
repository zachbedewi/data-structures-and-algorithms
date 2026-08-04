class Solution {
  public:
    vector<int> findMissingElements(vector<int> &nums) {
        ranges::sort(nums);
        vector<int> res;

        auto curr{nums[0] + 1};
        for (auto i{1uz}; i < nums.size(); ++curr) {
            if (nums[i] != curr) {
                res.push_back(curr);
            } else {
                ++i;
            }
        }

        return res;
    }
};
