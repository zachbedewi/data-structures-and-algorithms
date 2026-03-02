class Solution {
public:
    long long putMarbles(vector<int>& weights, int k) {
        const int n = weights.size();
        vector<long long> candidates;
        for (int i = 0; i < n - 1; ++i) {
            candidates.push_back(weights[i] + weights[i + 1]);
        }

        ranges::sort(candidates);

        long long minScore = 0;
        long long maxScore = 0;
        for (int i = 0; i < k - 1; ++i) {
            minScore += candidates[i];
            maxScore += candidates[n - i - 2];
        }

        return maxScore - minScore;
    }
};
