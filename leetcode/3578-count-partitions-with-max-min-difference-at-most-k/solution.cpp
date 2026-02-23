class Solution {
public:
    int countPartitions(vector<int>& nums, int k) {
        const int n = nums.size();
        vector<int> memo(n + 1, 0);
        memo[0] = 1;

        deque<int> max;
        deque<int> min;

        long long prefixSum = 1;
        for (int l = 0, r = 0; r < n; ++r) {

            while (!max.empty() && nums[max.back()] < nums[r]) {
                max.pop_back();
            }
            max.push_back(r);

            while (!min.empty() && nums[min.back()] > nums[r]) {
                min.pop_back();
            }
            min.push_back(r);

            while (nums[max.front()] - nums[min.front()] > k) {
                prefixSum = (prefixSum - memo[l++] + MODULUS) % MODULUS;
                if (max.front() < l) {
                    max.pop_front();
                }
                if (min.front() < l) {
                    min.pop_front();
                }
            }

            memo[r + 1] = prefixSum;
            prefixSum = (prefixSum + memo[r + 1]) % MODULUS;
        }

        return memo[n];
    }

private:
    static constexpr int MODULUS = 1'000'000'007;
};
