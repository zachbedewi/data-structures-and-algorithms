class FreqStack {
public:
    FreqStack() : frequencies{}, maxHeap{}, size{} {}

    void push(int val) {
        maxHeap.push({++frequencies[val], ++size, val});
    }

    int pop() {
        const auto [_, _, val] = maxHeap.top();
        maxHeap.pop();
        --frequencies[val];
        return val;
    }

private:
    unordered_map<int, int> frequencies;
    priority_queue<tuple<int, int, int>> maxHeap;
    size_t size;
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */
