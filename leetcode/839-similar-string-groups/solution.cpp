class union_find {
  public:
    explicit union_find(const int n)
        : parent_(n, 0), size_(n, 1), components_{n} {
        iota(parent_.begin(), parent_.end(), 0);
    }

    int find(int u) {
        if (u == parent_[u]) {
            return u;
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
        size_[u] += size_[v];
        parent_[v] = u;
        --components_;
    }

    int numComponents() { return components_; }

  private:
    vector<int> parent_;
    vector<int> size_;
    int components_;
};

class Solution {
  public:
    int numSimilarGroups(vector<string> &strs) {
        union_find uf{static_cast<int>(strs.size())};
        for (int i = 0; i < strs.size(); ++i) {
            for (int j = i + 1; j < strs.size(); ++j) {
                if (areSimilar(strs[i], strs[j])) {
                    uf.unite(i, j);
                }
            }
        }
        return uf.numComponents();
    }

  private:
    bool areSimilar(const string &word1, const string &word2) {
        int swaps = 0;
        for (int i = 0; i < word1.size(); ++i) {
            if (word1[i] != word2[i] && ++swaps > 2) {
                return false;
            }
        }

        return true;
    }
};
