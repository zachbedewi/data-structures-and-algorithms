class Solution {
  public:
    bool stoneGameIX(vector<int> &stones) {
        vector<int> remainderCounts(3, 0);
        for (auto const stone : stones) {
            ++remainderCounts[stone % 3];
        }

        int const n = stones.size();
        return solve(remainderCounts, n, 1) || solve(remainderCounts, n, 2);
    }

  private:
    bool solve(vector<int> remainderCounts, int n, int remainder) {
        if (!remainderCounts[remainder]) {
            return false;
        }

        --remainderCounts[remainder];

        auto sum{remainder};
        for (int i = 1; i < n; ++i) {
            if (remainderCounts[1] && (sum + 1) % 3) {
                --remainderCounts[1];
                ++sum;
            } else if (remainderCounts[2] && (sum + 2) % 3) {
                --remainderCounts[2];
                sum += 2;
            } else if (remainderCounts[0] && (sum + 3) % 3) {
                --remainderCounts[0];
                sum += 3;
            } else {
                return i % 2 == 1;
            }
        }

        return false;
    }
};
