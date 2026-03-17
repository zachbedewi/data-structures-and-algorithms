class Solution {
public:
    bool isValid(string s) {
        unordered_map<char, char> closeToOpen {
            {')', '('},
            {'}', '{'},
            {']', '['}
        };
        stack<char> st;

        for (char c : s) {
            if (closeToOpen.count(c)) {
                if (!st.empty() && st.top() == closeToOpen[c]) {
                    st.pop();
                } else {
                    return false;
                }
            } else {
                st.push(c);
            }
        }

        return st.empty();
    }
};
