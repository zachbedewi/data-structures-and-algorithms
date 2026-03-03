class Solution {
public:
    int minimumOperations(vector<int>& nums, int start, int goal) {
        queue<int> q {{ start }};
        unordered_set<int> visited { start };

        for (int step = 1; !q.empty(); ++step) {
            for (int sz = q.size(); sz > 0; --sz) {
                const auto x = q.front();
                q.pop();
                for (const int num : nums) {
                    for (const int res : {x + num, x - num, x ^ num}) {
                        if (res == goal) {
                            return step;
                        }
                        if (res < 0 || res > 1000 || visited.count(res)) {
                            continue;
                        }
                        visited.insert(res);
                        q.push(res);
                    }
                }
            }
        }

        return -1;
    }
};
