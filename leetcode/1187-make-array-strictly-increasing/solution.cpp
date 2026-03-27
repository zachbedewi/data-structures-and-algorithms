class Solution {
public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        set<int> pool{arr2.begin(), arr2.end()};

        unordered_map<int, int> dp{{-1, 0}};

        for (const auto num : arr1) {
            unordered_map<int, int> newDp;
            for (const auto& [prev, operations] : dp) {
                if (num > prev) {
                    if (!newDp.count(num) || newDp[num] > operations) {
                        newDp[num] = operations;
                    }
                }
                if (const auto it = pool.upper_bound(prev); it != pool.cend()) {
                    newDp[*it] = min(newDp.contains(*it) ? newDp[*it] : INT_MAX, operations + 1);
                }
            }
            dp = move(newDp);
        }

        if (dp.empty()) {
            return -1;
        }

        int res = INT_MAX;
        for (const auto& [_, operations] : dp) {
            res = min(res, operations);
        }
        return res;
    }
};
