  class Solution {
  public:
      int numSquarefulPerms(vector<int>& nums) {
          sort(nums.begin(), nums.end());
          int n = nums.size(), res = 0;
          vector<bool> used(n, false);

          auto isSquare = [](int x) {
              int s = sqrt(x);
              return s * s == x || (s + 1) * (s + 1) == x;
          };

          function<void(int, int)> dfs = [&](int depth, int prev) {
              if (depth == n) { res++; return; }
              for (int i = 0; i < n; ++i) {
                  if (used[i]) continue;
                  if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue;
                  if (depth > 0 && !isSquare(prev + nums[i])) continue;
                  used[i] = true;
                  dfs(depth + 1, nums[i]);
                  used[i] = false;
              }
          };

          dfs(0, -1);
          return res;
      }
  };
