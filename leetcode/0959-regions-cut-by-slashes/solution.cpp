class UnionFind {
  public:
    explicit UnionFind(std::size_t n)
        : n_{4 * n * n}, parent_(4 * n * n, 0), size_(4 * n * n, 1) {
        iota(parent_.begin(), parent_.end(), 0);
    }

    int find(int u) {
        if (parent_[u] == u) {
            return parent_[u];
        }
        return parent_[u] = find(parent_[u]);
    }

    void unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v)
            return;

        if (size_[u] < size_[v]) {
            swap(u, v);
        }

        parent_[v] = u;
        size_[u] += size_[v];
        --n_;
    }

    int numComponents() { return n_; }

  private:
    vector<int> parent_;
    vector<int> size_;
    std::size_t n_;
};

class Solution {
  public:
    int regionsBySlashes(vector<string> &grid) {
        auto const n = grid.size();
        UnionFind uf(n);

        auto node = [n](int i, int j, int t) { return (i * n + j) * 4 + t; };

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                char c = grid[i][j];

                if (c == ' ') {
                    uf.unite(node(i, j, 0), node(i, j, 1));
                    uf.unite(node(i, j, 1), node(i, j, 2));
                    uf.unite(node(i, j, 2), node(i, j, 3));
                } else if (c == '/') {
                    uf.unite(node(i, j, 0), node(i, j, 3));
                    uf.unite(node(i, j, 1), node(i, j, 2));
                } else {
                    uf.unite(node(i, j, 0), node(i, j, 1));
                    uf.unite(node(i, j, 2), node(i, j, 3));
                }

                if (i + 1 < n) {
                    uf.unite(node(i, j, 2), node(i + 1, j, 0));
                }

                if (j + 1 < n) {
                    uf.unite(node(i, j, 1), node(i, j + 1, 3));
                }
            }
        }

        return uf.numComponents();
    }
};
