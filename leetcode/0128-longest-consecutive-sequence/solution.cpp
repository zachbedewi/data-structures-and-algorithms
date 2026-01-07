class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> numsSet {nums.begin(), nums.end()};

        int maxLength = 0;
        for (int num : numsSet) {
            if (!numsSet.count(num - 1)) {
                int length = 1;
                while (numsSet.count(num + length)) {
                    ++length;
                }
                maxLength = max(maxLength, length);
            }
        }

        return maxLength;
    }
};
