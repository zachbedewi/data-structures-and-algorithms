class Solution {
public:
    vector<int> smallestTrimmedNumbers(vector<string>& nums, vector<vector<int>>& queries) {
        vector<int> ans;

        for (const auto& query : queries) {
            const int k = query[0];
            const int trim = query[1];
            priority_queue<pair<string, int>> maxHeap;

            for (int i = 0; i < nums.size(); ++i) {
                const string trimmed = nums[i].substr(nums[i].length() - trim, trim);
                maxHeap.push({trimmed, i});
                if (maxHeap.size() > k) {
                    maxHeap.pop();
                }
            }

            ans.push_back(maxHeap.top().second);
        }

        return ans;
    }
};
