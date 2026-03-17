class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        const int n = nums.size();
        vector<long> prefix(1, nums[0]);
        for (int i = 1; i < n; ++i) {
            prefix.push_back(prefix.back() + nums[i]);
        }

        deque<int> dq;
        int res = n + 1;
        for (int i = 0; i < n; ++i) {
            if (prefix[i] >= k) {
                res = min(res, i + 1);
            }

            // d.front() is the smallest index in the deque
            while (!dq.empty() && prefix[i] - prefix[dq.front()] >= k) {
                res = min(res, i - dq.front());
                dq.pop_front();
            }

            // Ensure that the deque only contains indices for which the prefix sum is increasing
            while (!dq.empty() && prefix[i] <= prefix[dq.back()]) {
                dq.pop_back();
            }

            dq.push_back(i);
        }

        return res <= n ? res : -1;
    }
};
