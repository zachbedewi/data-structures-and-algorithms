class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {
        const auto n {arr.size()};
        long long res = 0;
        stack<int> st;

        const auto process = [&](const int curr, const int r) {
            const int l = st.empty() ? -1 : st.top();
            long long count = static_cast<long long>(arr[curr]) * (r - curr) % MOD;
            count = count * (curr - l) % MOD;
            res = (res + count) % MOD;
        };

        for (int i = 0; i < n; ++i) {
            while (!st.empty() && arr[i] < arr[st.top()]) {
                int curr = st.top();
                st.pop();
                process(curr, i);
            }
            st.push(i);
        }

        while (!st.empty()) {
                const int curr = st.top();
                st.pop();
                process(curr, n);
        }

        return static_cast<int>(res);
    }

private:
    static constexpr int MOD = 1e9 + 7;
};
