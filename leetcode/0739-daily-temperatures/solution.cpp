class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> res(temperatures.size(), 0);
        stack<int> stack;

        for (int i = 0; i < temperatures.size(); i++) {
            int t = temperatures[i];
            while (!stack.empty() && t > temperatures[stack.top()]) {
                int j = stack.top();
                stack.pop();
                res[j] = i - j;
            }
            stack.push(i);
        }

        return res;
    }
};
