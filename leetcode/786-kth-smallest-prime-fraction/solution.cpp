class Solution {
  public:
    vector<int> kthSmallestPrimeFraction(vector<int> &arr, int k) {
        auto comp = [](auto &a, auto &b) { return get<0>(a) < get<0>(b); };
        priority_queue<tuple<double, int, int>, vector<tuple<double, int, int>>,
                       decltype(comp)>
            pq(comp);

        for (int i = 0; i < arr.size(); ++i) {
            for (int j = i + 1; j < arr.size(); ++j) {
                pq.push(
                    {static_cast<double>(arr[i]) / static_cast<double>(arr[j]),
                     arr[i], arr[j]});
                if (pq.size() > k) {
                    pq.pop();
                }
            }
        }

        return {get<1>(pq.top()), get<2>(pq.top())};
    }
};
