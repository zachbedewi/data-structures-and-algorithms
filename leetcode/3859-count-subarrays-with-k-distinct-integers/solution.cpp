class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k, int m) {
        unordered_map<int, int> distinctFrequency;
        unordered_map<int, int> thresholdFrequency;
        long long thresholdCount = 0;

        long long res = 0;
        // distinctLeft := The leftmost index s.t. |[distinctLeft, r]| <= k
        // thresholdLeft := The leftmost index s.t. |[thresholdLeft, r]| < k and all
        // elements in the range have frequency >= m
        for (int distinctLeft = 0, thresholdLeft = 0, r = 0; r < nums.size(); ++r) {
            ++distinctFrequency[nums[r]];
            while (distinctFrequency.size() > k) {
                if (--distinctFrequency[nums[distinctLeft]] == 0) {
                    distinctFrequency.erase(nums[distinctLeft]);
                }
                ++distinctLeft;
            }

            if (++thresholdFrequency[nums[r]] == m) {
                ++thresholdCount;
            }
            while (thresholdCount >= k) {
                if (thresholdFrequency[nums[thresholdLeft]]-- == m) {
                    --thresholdCount;
                }
                ++thresholdLeft;
            }
            if (thresholdLeft > distinctLeft) {
                res += thresholdLeft - distinctLeft;
            }
        }

        return res;
    }
};
