class Solution {
  public:
    int minSubarray(vector<int> &nums, int p) {
        auto need{0};
        for (auto const num : nums) {
            need = (need + num) % p;
        }

        unordered_map<int, int> lastSeenIdx{};
        lastSeenIdx[0] = -1;

        int res = nums.size();
        int currRemainder = 0;
        for (int i = 0; i < nums.size(); ++i) {
            currRemainder = (currRemainder + nums[i]) % p;
            lastSeenIdx[currRemainder] = i;
            int want = (currRemainder - need + p) % p;
            if (lastSeenIdx.contains(want)) {
                res = min(res, i - lastSeenIdx[want]);
            }
        }

        return res == nums.size() ? -1 : res;
    }
};
