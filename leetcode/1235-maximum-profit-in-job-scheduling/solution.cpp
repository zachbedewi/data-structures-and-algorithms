class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        const int n = startTime.size();

        vector<vector<int>> jobs;
        for (int i = 0; i < n; ++i) {
            jobs.push_back({endTime[i], startTime[i], profit[i]});
        }
        ranges::sort(jobs);

        // Memo[i] is the max profit you can make using jobs that end before or at time i
        map<int, int> memo {{0, 0}};
        for (auto& job : jobs) {
            int cur = prev(memo.upper_bound(job[1]))->second + job[2];
            if (cur > memo.rbegin()->second)
                memo[job[0]] = cur;
        }

        return memo.rbegin()->second;
    }
};
