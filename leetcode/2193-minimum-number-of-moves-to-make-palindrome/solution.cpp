class Solution {
  public:
    int minMovesToMakePalindrome(string s) {
        auto res{0};

        while (s.size()) {
            auto i{s.find(s.back())};
            if (i == s.size() - 1) {
                // Move character to the center of the string
                res += static_cast<int>(i / 2);
            } else {
                // Move character to the end
                res += i;
                s.erase(i, 1);
            }
            s.pop_back();
        }

        return res;
    }
};
