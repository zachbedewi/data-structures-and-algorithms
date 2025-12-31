//
// STATUS: Reviewed 12/31/2025
class Solution {
  public:

  vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> numToIndex;

    for (int i = 0; i < nums.size(); ++i) {
      if (const auto it = seen.find(target - nums[i]); it != seen.cend()) {
        return {it->second, i};
      }
      seen[nums[i]] = i;
    }

    throw;
  }

};
