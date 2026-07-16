class Solution {
  public:
    int superpalindromesInRange(string left, string right) {
        long long const lo = stoll(left);
        long long const hi = stoll(right);
        int count = 0;
        for (auto const root : buildPalindromicRoots()) {
            long long const square = root * root;
            if (lo <= square && square <= hi &&
                isPalindrome(to_string(square))) {
                ++count;
            }
        }
        return count;
    }

  private:
    vector<long long> buildPalindromicRoots() {
        vector<long long> roots;
        for (int i = 1; i <= 9; ++i) {
            roots.push_back(i);
        }

        for (int i = 1; i < 10000; ++i) {
            string half = to_string(i);
            string reversedHalf(half.rbegin(), half.rend());
            roots.push_back(stoll(half + reversedHalf));
            for (char mid = '0'; mid < '9'; ++mid) {
                roots.push_back(stoll(half + mid + reversedHalf));
            }
        }
        sort(roots.begin(), roots.end());
        return roots;
    }

    bool isPalindrome(string s) {
        int l = 0;
        int r = s.length() - 1;
        while (l < r) {
            if (s[l++] != s[r--]) {
                return false;
            }
        }

        return true;
    }
};
