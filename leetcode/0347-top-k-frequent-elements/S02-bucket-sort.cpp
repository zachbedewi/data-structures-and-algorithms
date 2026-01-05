class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        for (const int num : nums) {
            ++count[num];
        }

        vector<vector<int>> frequencies(nums.size() + 1);
        for (const auto& [num, frequency] : count) {
            frequencies[frequency].push_back(num);
        }

        vector<int> res;
        for (int i = frequencies.size() - 1; i > 0; --i) {
            for (const int num : frequencies[i]) {
                res.push_back(num);
                if (res.size() == k) {
                    return res;
                }
            }
        }

        throw;
    }
};
