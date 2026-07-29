class Solution {
  public:
    int waysToPartition(vector<int> &nums, int k) {
        auto const n = nums.size();

        vector<long long> prefix(n, 0);
        vector<long long> suffix(n, 0);

        prefix[0] = nums[0];
        suffix[n - 1] = nums[n - 1];
        for (int i = 1; i < n; ++i) {
            prefix[i] = prefix[i - 1] + nums[i];
            suffix[n - i - 1] = suffix[n - i] + nums[n - i - 1];
        }

        unordered_map<long long, long long> processed;
        unordered_map<long long, long long> toProcess;

        for (int i = 0; i < n - 1; ++i) {
            ++toProcess[prefix[i] - suffix[i + 1]];
        }

        auto res{toProcess[0]};

        for (int i = 0; i < n; ++i) {
            auto pivotPointCount{0LL};
            auto netIncrease = k - nums[i];

            if (processed.contains(netIncrease)) {
                pivotPointCount += processed[netIncrease];
            }
            if (toProcess.contains(-netIncrease)) {
                pivotPointCount += toProcess[-netIncrease];
            }

            res = max(res, pivotPointCount);

            if (i < n - 1) {
                auto const partitionVal = prefix[i] - suffix[i + 1];
                ++processed[partitionVal];
                --toProcess[partitionVal];
                if (!toProcess[partitionVal]) {
                    toProcess.erase(partitionVal);
                }
            }
        }

        return res;
    }
};
