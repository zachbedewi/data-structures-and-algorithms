class Solution {
  public:
    int numSubmatrixSumTarget(vector<vector<int>> &matrix, int target) {
        const auto n = matrix.size();
        const auto m = matrix[0].size();

        for (int r = 0; r < n; ++r) {
            for (int c = 1; c < m; ++c) {
                matrix[r][c] += matrix[r][c - 1];
            }
        }

        int count = 0;

        for (int c1 = 0; c1 < m; ++c1) {
            for (int c2 = c1; c2 < m; ++c2) {
                unordered_map<int, int> freqs;
                freqs[0] = 1;

                int sum = 0;
                for (int r = 0; r < n; ++r) {
                    sum += matrix[r][c2] - (c1 > 0 ? matrix[r][c1 - 1] : 0);
                    if (freqs.contains(sum - target)) {
                        count += freqs[sum - target];
                    }

                    ++freqs[sum];
                }
            }
        }

        return count;
    }
};
