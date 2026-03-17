class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int maxArea {}, n {static_cast<int>(heights.size())};
        stack<int> st;

        for (int i = 0; i <= n; i++) {
            while (!st.empty() && (i == n || heights[st.top()] >= heights[i])) {
                int height = heights[st.top()];
                st.pop();
                int width = st.empty() ? i : i - st.top() - 1;
                maxArea = max(maxArea, width * height);
            }
            st.push(i);
        }

        return maxArea;
    }
};
