class Solution {
public:
    int maxEqualFreq(vector<int>& nums) {
        const int n = nums.size();
        unordered_map<int, int> frequency;
        unordered_map<int, int> frequencyCount;

        int res = 0;
        int maxFrequency = 0;
        for (int i = 0; i < n; ++i) {
            const int num = nums[i];

            --frequencyCount[frequency[num]];
            ++frequency[num];
            ++frequencyCount[frequency[num]];

            maxFrequency = max(maxFrequency, frequency[num]);

            if (maxFrequency == 1
                || maxFrequency * frequencyCount[maxFrequency] == i
                || (maxFrequency - 1) * (frequencyCount[maxFrequency - 1] + 1) == i) {
                res = i + 1;
            }
        }

        return res;
    }
};
