class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        array<int, 26> cnt{};
        for (char c : s){
            ++cnt[c - 'a'];
        }

        string mid;
        for (int i = 0; i < cnt.size(); ++i) {
            if (cnt[i] % 2) {
                if (!mid.empty()) {
                    return "";
                }
                mid = string(1, 'a' + i);
            }
            cnt[i] /= 2;
        }

        int halfLen = s.size() / 2;
        string left(halfLen, ' ');

        auto build = [&](this auto&& build, int k, bool isGreater) -> bool {
            if (k == halfLen) {
                string res = left + mid + string(left.rbegin(), left.rend());
                return res > target;
            }
            char start = isGreater ? 'a' : target[k];
            for (char c = start; c <= 'z'; ++c) {
                if (cnt[c - 'a'] > 0) {
                    left[k] = c;
                    cnt[c - 'a']--;
                    if (build(k + 1, isGreater || c > target[k]))
                        return true;
                    cnt[c - 'a']++;
                }
            }
            return false;
        };

        if (build(0, false))
            return left + mid + string(left.rbegin(), left.rend());
        return "";
    }
};
