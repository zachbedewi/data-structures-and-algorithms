class Solution {
  public:
    bool canConstruct(string ransomNote, string magazine) {
        if (ransomNote.length() > magazine.length()) {
            return false;
        }

        std::array<int, 26> count;
        for (auto const c : magazine) {
            ++count[c - 'a'];
        }

        for (auto const c : ransomNote) {
            if (count[c - 'a'] == 0) {
                return false;
            }
            --count[c - 'a'];
        }
        return true;
    }
};
