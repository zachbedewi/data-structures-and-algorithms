class Solution {
  public:
    bool stoneGameIX(vector<int> &stones) {
        vector<int> remainderCounts(3, 0);
        for (auto const stone : stones) {
            ++remainderCounts[stone % 3];
        }

        if (remainderCounts[0] % 2 == 0) {
            return remainderCounts[1] > 0 && remainderCounts[2] > 0;
        }

        return abs(remainderCounts[1] - remainderCounts[2]) > 2;
    }
};
