class UnionFind {
  public:
    explicit UnionFind(int n) : n_{n}, parent_(n, 0), size_(n, 1) {
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
    int n_;
};

class Solution {
  public:
    int minSwapsCouples(vector<int> &row) {
        auto const numCouples = static_cast<int>(row.size() / 2);
        UnionFind uf(numCouples);

        for (int i = 0; i < row.size(); i += 2) {
            int coupleA = row[i] / 2;
            int coupleB = row[i + 1] / 2;
            uf.unite(coupleA, coupleB);
        }

        return numCouples - uf.numComponents();
    }
};
