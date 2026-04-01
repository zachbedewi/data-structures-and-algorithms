class Solution {
public:
    int maxSumMinProduct(vector<int>& nums) {
        // prefix sum so we can quickly find sum of subarray
        // Keep track of min value in subarray
        const int n = nums.size();
        vector<long long> prefixSum(n + 1);
        for (int i = 0; i < n; ++i) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }

        stack<int> st;
        long long res = 0;
        for (int i = 0; i <= n; ++i) {
            while (!st.empty() && (i == n || nums[i] < nums[st.top()])) {
                const int minIndex = st.top();
                st.pop();
                const int leftBound = st.empty() ? 0 : st.top() + 1;
                res = max(res, nums[minIndex] * (prefixSum[i] - prefixSum[leftBound]));
            }
            st.push(i);
        }

        return res % MOD;
    }

private:
    static constexpr int MOD = 1'000'000'007;
};
