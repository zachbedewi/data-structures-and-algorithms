class Solution {
public:
    bool isPalindrome(string s) {
        s.erase(remove_if(s.begin(), s.end(), [](unsigned char c) {
            return !isalnum(c) || isspace(c);
        }), s.end());
        transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
            return tolower(c);
        });

        int left = 0;
        int right = s.length() - 1;

        while (left <= right) {
            if (s[left++] != s[right--]) {
                return false;
            }
        }

        return true;
    }
};
