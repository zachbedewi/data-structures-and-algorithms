class FreqStack {
public:
    FreqStack() : frequencies{}, stacks{}, maxFrequency{} {}

    void push(int val) {
        maxFrequency = max(maxFrequency, ++frequencies[val]);
        stacks[frequencies[val]].push(val);
    }

    int pop() {
        const int val = stacks[maxFrequency].top();
        stacks[maxFrequency].pop();
        if (stacks[maxFrequency].empty()) {
            --maxFrequency;
        }
        --frequencies[val];
        return val;    }

private:
    unordered_map<int, int> frequencies;
    unordered_map<int, stack<int>> stacks;
    int maxFrequency;
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */
