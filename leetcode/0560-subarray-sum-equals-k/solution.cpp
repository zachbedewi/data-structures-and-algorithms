class Solution {
  public:
    int subarraySum(vector<int> &nums, int k) {
        unordered_map<int, int> freqs;
        freqs[0] = 1;
        int sum = 0;
        int res = 0;

        for (const auto n : nums) {
            sum += n;

            if (freqs.contains(sum - k)) {
                res += freqs[sum - k];
            }

            ++freqs[sum];
        }

        return res;
    }
};
