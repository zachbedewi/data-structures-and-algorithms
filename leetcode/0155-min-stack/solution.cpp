class MinStack {
private:
    stack<long> stack;
    long currMin;

public:
    MinStack() {}

    void push(int val) {
        if (stack.empty()) {
            stack.push(0);
            currMin = val;
        } else {
            stack.push(val - currMin);
            if (val < currMin) {
                currMin = val;
            }
        }
    }

    void pop() {
        if (stack.empty()) {
            return;
        }

        long top = stack.top();
        stack.pop();

        if (top < 0) {
            currMin = currMin - top;
        }
    }

    int top() {
        long top = stack.top();
        return (top > 0) ? top + currMin : (int)currMin;
    }

    int getMin() {
        return (int)currMin;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
