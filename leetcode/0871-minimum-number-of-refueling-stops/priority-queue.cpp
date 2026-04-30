class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int i = 0;
        int res = 0;
        int remainingFuel = startFuel;

        priority_queue<int> pq;
        for (; remainingFuel < target; ++res) {
            while (i < stations.size() && stations[i][0] <= remainingFuel) {
                pq.push(stations[i++][1]);
            }

            if (pq.empty()) {
                return -1;
            }
            remainingFuel += pq.top();
            pq.pop();
        }

        return res;
    }
};
