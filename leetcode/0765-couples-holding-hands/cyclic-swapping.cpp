class Solution {
  public:
    int minSwapsCouples(vector<int> &row) {
        auto const n = row.size();
        vector<int> position(n, 0);

        for (int i = 0; i < n; ++i) {
            position[row[i]] = i;
        }

        int res = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = partner(position[partner(row[i])]); j != i;
                 j = partner(position[partner(row[i])])) {
                swap(row[i], row[j]);
                swap(position[row[i]], position[row[j]]);
                ++res;
            }
        }

        return res;
    }

  private:
    int partner(int n) { return n % 2 == 0 ? n + 1 : n - 1; }
};
