class Solution {
  public:
    vector<int> canSeePersonsCount(vector<int> &heights) {
        auto const n = heights.size();

        stack<int> st;
        vector<int> res(n, 0);
        for (int i = n - 1; i >= 0; --i) {
            while (!st.empty() && heights[st.top()] <= heights[i]) {
                ++res[i];
                st.pop();
            }
            if (!st.empty()) {
                ++res[i];
            }
            st.push(i);
        }

        return res;
    }
};
