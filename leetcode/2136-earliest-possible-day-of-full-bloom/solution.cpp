class Solution {
public:
    int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {
        const int n = plantTime.size();

        vector<pair<int, int>> totalTime;
        for (const auto& [plant, grow] : views::zip(plantTime, growTime)) {
            totalTime.push_back({grow, plant});
        }
        ranges::sort(totalTime);

        int res = 0;
        for (const auto& [grow, plant] : totalTime) {
            res = max(res, grow);
            res += plant;
        }

        return res;
    }
};
