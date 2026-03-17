class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> stack;

        for (string s : tokens) {
            if (s == "+") {
                int rhs = stack.top();
                stack.pop();
                int lhs = stack.top();
                stack.pop();
                stack.push(lhs + rhs);
            } else if (s == "-") {
                int rhs = stack.top();
                stack.pop();
                int lhs = stack.top();
                stack.pop();
                stack.push(lhs - rhs);
            } else if (s == "*") {
                int rhs = stack.top();
                stack.pop();
                int lhs = stack.top();
                stack.pop();
                stack.push(lhs * rhs);
            } else if (s == "/") {
                int rhs = stack.top();
                stack.pop();
                int lhs = stack.top();
                stack.pop();
                stack.push(lhs / rhs);
            } else {
                stack.push(stoi(s));
            }
        }

        return stack.top();
    }
};
