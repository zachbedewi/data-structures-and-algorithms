class Solution {
  public:
    long long minimumDifference(vector<int> &nums) {
        ssize_t const n = nums.size();
        ssize_t const k = n / 3;

        vector<long long> minLeftSum(n, 0);
        priority_queue<long long> maxLeftHeap;
        auto leftSum{0LL};
        for (int i = 0; i < k; ++i) {
            leftSum += nums[i];
            maxLeftHeap.push(nums[i]);
        }
        minLeftSum[k - 1] = leftSum;

        for (int i = k; i < n - k; ++i) {
            if (!maxLeftHeap.empty() && nums[i] < maxLeftHeap.top()) {
                leftSum += nums[i] - maxLeftHeap.top();
                maxLeftHeap.pop();
                maxLeftHeap.push(nums[i]);
            }
            minLeftSum[i] = leftSum;
        }

        vector<long long> maxRightSum(n, 0);
        priority_queue<long long, vector<long long>, greater<>> minRightHeap;
        auto rightSum{0LL};
        for (int i = n - 1; i >= n - k; --i) {
            rightSum += nums[i];
            minRightHeap.push(nums[i]);
        }
        maxRightSum[n - k] = rightSum;

        for (int i = n - k - 1; i >= k - 1; --i) {
            if (!minRightHeap.empty() && nums[i] > minRightHeap.top()) {
                rightSum += nums[i] - minRightHeap.top();
                minRightHeap.pop();
                minRightHeap.push(nums[i]);
            }
            maxRightSum[i] = rightSum;
        }

        auto res{numeric_limits<long long>::max()};
        for (int i = k - 1; i < n - k; ++i) {
            res = min(res, minLeftSum[i] - maxRightSum[i + 1]);
        }
        return res;
    }
};
