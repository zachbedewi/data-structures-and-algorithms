class UnionFind {
    vector<int> parent_{};
    vector<int> size_{};
    int n_{0};

  public:
    explicit UnionFind(int n) : parent_(n + 1, 0), size_(n + 1, 0), n_{n} {
        iota(parent_.begin(), parent_.end(), 0);
    };

    int find(int const u) {
        if (parent_[u] == u) {
            return u;
        }
        return parent_[u] = find(parent_[u]);
    }

    bool unite(int const u, int const v) {
        auto pU = find(u);
        auto pV = find(v);
        if (pU == pV)
            return false;

        if (size_[pU] < size_[pV])
            swap(pU, pV);

        parent_[pV] = pU;
        size_[pU] += size_[pV];
        --n_;
        return true;
    }

    int numComponents() { return n_; }
};

class Solution {
  public:
    int maxNumEdgesToRemove(int n, vector<vector<int>> &edges) {
        UnionFind bob{n};
        UnionFind alice{n};

        ranges::sort(edges, ranges::greater{},
                     [](auto const &e) { return e[0]; });

        int numEdges = 0;
        for (auto const &edge : edges) {
            auto const type = edge[0];
            auto const u = edge[1];
            auto const v = edge[2];
            switch (type) {
            case 3:
                numEdges += (bob.unite(u, v) | alice.unite(u, v));
                break;
            case 2:
                numEdges += bob.unite(u, v);
                break;
            case 1:
                numEdges += alice.unite(u, v);
                break;
            }
        }

        return (bob.numComponents() == 1 && alice.numComponents() == 1)
                   ? (edges.size() - numEdges)
                   : -1;
    }
};
