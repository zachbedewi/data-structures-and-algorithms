class Solution {
  public:
    int countTriplets(vector<int> &nums) {
        unordered_map<int, int> tuples;
        for (auto const a : nums) {
            for (auto const b : nums) {
                ++tuples[a & b];
            }
        }

        auto res{0};
        for (auto const a : nums) {
            for (auto const tuple : tuples) {
                if ((a & tuple.first) == 0) {
                    res += tuple.second;
                }
            }
        }

        return res;
    }
};
