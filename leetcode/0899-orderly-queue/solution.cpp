class Solution {
public:
    string orderlyQueue(string s, int k) {
        if (k == 1) {
            return findMinimumRotation(s);
        }
        ranges::sort(s);
        return s;
    }

private:
    string findMinimumRotation(string s) {
        string res = s;
        for (int i = 1; i < s.length(); i++)
            res = min(res, s.substr(i) + s.substr(0, i));
        return res;
    }
};
