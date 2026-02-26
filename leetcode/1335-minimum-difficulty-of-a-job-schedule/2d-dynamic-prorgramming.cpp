class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        const int n = jobDifficulty.size();
        if (n < d) {
            return -1;
        }
        vector<vector<int>> memo(d, vector<int>(n));
        memo[0][0] = jobDifficulty[0];
        for (int i = 1; i < n; ++i) {
            memo[0][i] = max(memo[0][i - 1], jobDifficulty[i]);
        }

        for (int numDays = 1; numDays < d; ++numDays) {
            for (int startingJob = numDays; startingJob < n; ++startingJob) {
                int currMax = jobDifficulty[startingJob];
                memo[numDays][startingJob] = numeric_limits<int>::max();
                for (int currentJob = startingJob; currentJob >= numDays; --currentJob) {
                    currMax = max(currMax, jobDifficulty[currentJob]);
                    memo[numDays][startingJob] = min(memo[numDays][startingJob], memo[numDays - 1][currentJob - 1] + currMax);
                }
            }
        }

        return memo[d - 1][n - 1];
    }
};
