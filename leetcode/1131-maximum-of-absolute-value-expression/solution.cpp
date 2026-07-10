class Solution {
  public:
    int maxAbsValExpr(vector<int> &arr1, vector<int> &arr2) {
        const auto n = arr1.size();

        // Represents arr1[i] + arr2[i] + i
        vector<int> sum1(n, 0);

        // Represents arr1[i] - arr2[i] + i
        vector<int> diff1(n, 0);

        // Represents arr1[i] + arr2[i] - i
        vector<int> sum2(n, 0);

        // Represents arr1[i] - arr2[i] - i
        vector<int> diff2(n, 0);

        for (int i = 0; i < n; ++i) {
            sum1[i] = arr1[i] + arr2[i] + i;
            diff1[i] = arr1[i] - arr2[i] + i;
            sum2[i] = arr1[i] + arr2[i] - i;
            diff2[i] = arr1[i] - arr2[i] - i;
        }

        return max(max(maximize(sum1), maximize(diff1)),
                   max(maximize(sum2), maximize(diff2)));
    }

  private:
    int maximize(vector<int> const &arr) {
        int maxSum = arr[0];
        int minSum = arr[0];
        for (int i = 1; i < arr.size(); ++i) {
            maxSum = max(maxSum, arr[i]);
            minSum = min(minSum, arr[i]);
        }
        return (maxSum - minSum);
    }
};
