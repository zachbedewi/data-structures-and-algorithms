class Solution {
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int diff) {
        // Rearranged Equation:
        // nums1[i] - nums2[i] <= nums1[j] - nums2[j] + diff
        // Need to find C[k] = nums1[k] - nums2[k] s.t. C[i] <= C[j] + diff
        const int n = nums1.size();
        vector<int> differences(n);

        for (int i = 0; i < n; ++i) {
            differences[i] = nums1[i] - nums2[i];
        }

        long long res = 0;
        mergeSort(differences, 0, differences.size() - 1, diff, res);
        return res;
    }

private:
    void mergeSort(vector<int>& differences, int l, int r, int diff, long long& res) {
        if (l >= r) {
            return;
        }

        const int m = l + (r - l) / 2;
        mergeSort(differences, l, m, diff, res);
        mergeSort(differences, m + 1, r, diff, res);
        merge(differences, l, m, r, diff, res);
    }

    void merge(vector<int>& differences, int l, int m, int r, int diff, long long& res) {
        int hi = m + 1;

        for (int i = l; i <= m; ++i) {
            while (hi <= r && differences[i] > differences[hi] + diff) {
                ++hi;
            }
            res += r - hi + 1;
        }

        vector<int> sorted(r - l + 1);
        int k = 0;
        int i = l;
        int j = m + 1;

        while (i <= m && j <= r) {
            if (differences[i] < differences[j]) {
                sorted[k++] = differences[i++];
            } else {
                sorted[k++] = differences[j++];
            }
        }

        while (i <= m) {
            sorted[k++] = differences[i++];
        }

        while (j <= r) {
            sorted[k++] = differences[j++];
        }

        copy(sorted.begin(), sorted.end(), differences.begin() + l);
    }
};
