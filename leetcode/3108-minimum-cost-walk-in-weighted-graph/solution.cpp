class UnionFind {
public:
    explicit UnionFind(int n)
        : parent_(n, 0)
        , size_(n, 1)
        , cost_(n, ~0) {
        std::iota(parent_.begin(), parent_.end(), 0);
    }

    int find(int const u) {
        if (u == parent_[u]) {
            return u;
        }
        return parent_[u] = find(parent_[u]);
    }

    bool unionSets(int const u, int const v, int const weight) {
        auto pU = find(u);
        auto pV = find(v);

        if (pU == pV) {
            cost_[pU] &= weight;
            return false;
        }

        if (size_[pU] < size_[pV]) {
            std::swap(pU, pV);
        }

        parent_[pV] = pU;
        size_[pU] += size_[pV];
        cost_[pU] &= cost_[pV];
        cost_[pU] &= weight;
        return true;
    }

    int cost(int u) {
        return cost_[u];
    }

private:
    std::vector<int> parent_;
    std::vector<int> size_;
    std::vector<int> cost_;
};

class Solution {
public:
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        UnionFind uf{n};

        for (auto const& edge : edges) {
            uf.unionSets(edge[0], edge[1], edge[2]);
        }

        std::vector<int> res{};
        for (auto const& q : query) {
            if (q[0] == q[1]) {
                res.push_back(0);
                continue;
            }

            auto const sP = uf.find(q[0]);
            auto const tP = uf.find(q[1]);

            if (sP != tP) {
                res.push_back(-1);
            } else {
                res.push_back(uf.cost(sP));
            }
        }

        return res;
    }
};

