class Solution {
  public:
    int maxSum(vector<int> &nums1, vector<int> &nums2) {
        int i = 0;
        int j = 0;
        int n = nums1.size();
        int m = nums2.size();
        long long a = 0;
        long long b = 0;

        while (i < n || j < m) {
            if (i < n && (j == m || nums1[i] < nums2[j])) {
                a += nums1[i++];
            } else if (j < m && (i == n || nums2[j] < nums1[i])) {
                b += nums2[j++];
            } else {
                a = b = (max(a, b) + nums1[i]) % MOD;
                ++i;
                ++j;
            }
        }
        return max(a, b) % MOD;
    }

    static constexpr int MOD = 1e9 + 7;
};
