class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> prefixProducts(nums.size(), 1);
        for (int i = 1; i < nums.size(); ++i) {
            prefixProducts[i] = nums[i - 1] * prefixProducts[i - 1];
        }

        vector<int> suffixProducts(nums.size(), 1);
        for (int i = nums.size() - 2; i >= 0; --i) {
            suffixProducts[i] = nums[i + 1] * suffixProducts[i + 1];
        }

        vector<int> res(nums.size(), 0);
        for (int i = 0; i < nums.size(); ++i) {
            res[i] = prefixProducts[i] * suffixProducts[i];
        }
        return res;
    }
};
