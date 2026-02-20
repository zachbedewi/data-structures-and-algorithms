class Solution {
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int diff) {
        // Rearranged Equation:
        // nums1[i] - nums2[i] <= nums1[j] - nums2[j] + diff
        // Need to find C[k] = nums1[k] - nums2[k] s.t. C[i] <= C[j] + diff
        long long res = 0;
        vector<int> differences;
        for (const auto& [num1, num2] : views::zip(nums1, nums2)) {
            res += distance(differences.begin(), ranges::upper_bound(differences, num1 - num2 + diff));
            differences.insert(ranges::lower_bound(differences, num1 - num2), num1 - num2);
        }

        return res;
    }
};
