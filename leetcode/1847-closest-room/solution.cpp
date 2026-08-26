class Solution {
  public:
    vector<int> closestRoom(vector<vector<int>> &rooms,
                            vector<vector<int>> &queries) {
        auto const cmp = [](std::vector<int> const &a,
                            std::vector<int> const &b) { return a[1] > b[1]; };
        for (auto i{0}; i < queries.size(); ++i) {
            queries[i].push_back(i);
        }

        std::ranges::sort(rooms, cmp);
        std::ranges::sort(queries, cmp);

        std::vector<int> res(queries.size());
        std::set<int> ids;
        auto i{0};
        for (auto const &query : queries) {
            auto const &preferred = query[0];
            auto const &minSize = query[1];
            auto const &idx = query[2];

            while (i < rooms.size() && rooms[i][1] >= minSize) {
                ids.insert(rooms[i++][0]);
            }

            if (ids.empty()) {
                res[idx] = -1;
                continue;
            }

            auto it = ids.lower_bound(preferred);
            auto id1 = it == std::begin(ids) ? -1 : *(std::prev(it));
            auto id2 = it == std::end(ids) ? -1 : *it;
            res[idx] = std::min(id1, id2) == -1 ? std::max(id1, id2)
                       : std::abs(id1 - preferred) <= std::abs(id2 - preferred)
                           ? id1
                           : id2;
        }
        return res;
    }
};
