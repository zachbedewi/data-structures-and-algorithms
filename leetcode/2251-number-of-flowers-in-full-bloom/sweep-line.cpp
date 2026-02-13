class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers,
                                 vector<int>& people) {
        map<int, int> line {{0, 0}};

        for (const auto& flower : flowers) {
            ++line[flower[0]];
            --line[flower[1] + 1];
        }

        for (auto it = next(line.begin()); it != line.end(); ++it) {
            it->second += prev(it)->second;
        }

        transform(people.begin(), people.end(), people.begin(), [&](auto time) {
            const auto it = prev(line.upper_bound(time));
            if (it->first <= time) {
                return it->second;
            }
            return 0;
        });

        return people;
    }
};
