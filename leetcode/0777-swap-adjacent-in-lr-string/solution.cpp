class Solution {
  public:
    bool canTransform(string start, string result) {
        auto n{start.length()};
        auto i{0uz};
        auto j{0uz};

        for (; i < n || j < n; ++i, ++j) {
            for (; i < n && start[i] == 'X'; ++i)
                ;
            for (; j < n && result[j] == 'X'; ++j)
                ;

            if (i == n || j == n) {
                return i == n && j == n;
            }

            if (start[i] != result[j])
                return false;

            if (start[i] == 'L' && i < j)
                return false;
            if (start[i] == 'R' && i > j)
                return false;
        }

        return true;
    }
};
