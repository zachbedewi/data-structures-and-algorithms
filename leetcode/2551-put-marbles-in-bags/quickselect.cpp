class Solution {
public:
    long long putMarbles(vector<int>& weights, int k) {
        const int n = weights.size();
        if (n <= 2 || n == k) {
            return 0;
        }

        vector<long long> candidates(n - 1, 0);
        for (int i = 0; i < n - 1; ++i) {
            candidates[i] = weights[i] + weights[i + 1];
        }

        nth_element(candidates.begin(), candidates.begin() + k - 1, candidates.end());
        const long long minScore = accumulate(candidates.begin(), candidates.begin() + k - 1, 0LL);

        nth_element(candidates.begin(), candidates.begin() + n - k, candidates.end());
        const long long maxScore = accumulate(candidates.begin() + n - k, candidates.end(), 0LL);

        return maxScore - minScore;
    }
};
