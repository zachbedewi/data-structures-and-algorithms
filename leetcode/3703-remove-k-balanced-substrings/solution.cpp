class Solution {
public:
    string removeSubstring(string s, int k) {
        stack<pair<char, int>> st;

        for (const char nextChar : s) {
            if (st.empty() || nextChar != st.top().first) {
                st.push({nextChar, 1});
            } else {
                const auto& [previousChar, count] = st.top();
                st.pop();
                st.push({nextChar, count + 1});
            }

            if (st.size() > 1) {
                auto [currChar, currCount] = st.top();
                st.pop();

                auto [prevChar, prevCount] = st.top();
                st.pop();

                if (currChar == ')' && prevChar == '(' && currCount >= k && prevCount >= k) {
                    currCount -= k;
                    prevCount -= k;
                }

                if (prevCount > 0) {
                    st.push({prevChar, prevCount});
                }
                if (currCount > 0) {
                    st.push({currChar, currCount});
                }
            }
        }

        string ans;
        while (!st.empty()) {
            const auto& [c, count] = st.top();
            st.pop();
            ans += string(count, c);
        }
        ranges::reverse(ans);
        return ans;
    }
};
