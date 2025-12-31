//
// TODO: Review
class Solution {
  public:

  bool isAnagram(string s, string t) {
    if (s.length() != t.length()) {
      return false;
    }

    vector<int> count(26, 0);

    for (const auto c : s) {
      ++count[c - 'a'];
    }

    for (const auto c : t) {
      if (count[c - 'a']-- == 0) {
        return false;
      }
    }

    return true;
  }

};
