class Solution {
  public:
    int maxPerformance(int n, vector<int> &speed, vector<int> &efficiency,
                       int k) {
        vector<pair<int, int>> engineers(n);
        for (int i = 0; i < n; ++i) {
            engineers[i] = {efficiency[i], speed[i]};
        }
        sort(rbegin(engineers), rend(engineers));
        priority_queue<int, vector<int>, greater<>> pq;
        long long totalSpeed = 0;
        long long res = 0;
        for (auto const &[e, s] : engineers) {
            pq.push(s);
            totalSpeed += s;
            if (pq.size() > k) {
                totalSpeed -= pq.top();
                pq.pop();
            }
            res = max(res, totalSpeed * e);
        }
        return res % MOD;
    }

  private:
    static constexpr int MOD = 1e9 + 7;
};
