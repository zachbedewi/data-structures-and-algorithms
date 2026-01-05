class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        for (const int num : nums) {
            ++count[num];
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
        for (const auto& [num, frequency] : count) {
            minHeap.emplace(frequency, num);
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }

        vector<int> res;
        while (!minHeap.empty()) {
            res.push_back(minHeap.top().second);
            minHeap.pop();
        }

        return res;
    }
};
