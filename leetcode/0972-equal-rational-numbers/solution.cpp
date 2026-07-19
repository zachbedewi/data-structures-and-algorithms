class Solution {
  public:
    bool isRationalEqual(string s, string t) {
        return computeValue(s) == computeValue(t);
    }

  private:
    double computeValue(const string &s) {
        auto i = s.find("(");

        if (i != string::npos) {
            auto base = s.substr(0, i);
            auto rep = s.substr(i + 1, s.length() - i - 2);
            for (int j = 0; j < 20; ++j) {
                base += rep;
            }
            return stod(base);
        }

        return stod(s);
    }
};
