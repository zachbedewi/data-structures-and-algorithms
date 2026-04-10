class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        // monotonic or sliding window
        // keep moving r until min or max is greater that minK or maxK
        // Once it is, move l until min or max is no longer in subarray.
        deque<int> maxQ;
        deque<int> minQ;

        long long res = 0;
        for (int l = 0, r = 0; r < nums.size(); ++r) {
            const int num = nums[r];
            if (num < minK || num > maxK) {
                maxQ.clear();
                minQ.clear();
                l = r + 1;
                continue;
            }

            while (!minQ.empty() && num <= nums[minQ.back()]) {
                minQ.pop_back();
            }
            minQ.push_back(r);

            while (!maxQ.empty() && num >= nums[maxQ.back()]) {
                maxQ.pop_back();
            }
            maxQ.push_back(r);

            if (nums[minQ.front()] == minK && nums[maxQ.front()] == maxK) {
                const int minimumStartingIndex = min(minQ.front(), maxQ.front());
                res += minimumStartingIndex - l + 1;
            }
        }

        return res;
    }
};
