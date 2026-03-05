class UnionFind {
public:

    UnionFind(int n) : parent(n), size(n, 1), numComponents(n) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int v) {
        if (v == parent[v]) {
            return v;
        }
        return parent[v] = find(parent[v]);
    }

    bool unionSets(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) {
            return false;
        }

        if (size[u] < size[v]) {
            swap(u, v);
        }
        parent[v] = u;
        size[u] += size[v];
        --numComponents;
        return true;
    }

    bool areConnected(int u, int v) {
        return find(u) == find(v);
    }

    int getNumComponents() {
        return numComponents;
    }

private:
    vector<int> parent;
    vector<int> size;
    int numComponents;
};

class Solution {
public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        UnionFind initialUf(n);

        int maxStability = numeric_limits<int>::max();
        for (const auto& edge : edges) {
            const bool must = edge[3] == 1;
            if (!must) {
                continue;
            }

            const int u = edge[0];
            const int v = edge[1];
            if (!initialUf.unionSets(u, v)) {
                return -1;
            }

            const int strength = edge[2];
            maxStability = min(maxStability, strength);
        }

        const auto check = [&](int stability) -> bool {
            if (stability > maxStability) {
                return false;
            }

            UnionFind uf(initialUf);

            vector<pair<int, int>> upgrade;
            for (const auto& edge : edges) {
                const bool must = edge[3] == 1;
                if (must) {
                    continue;
                }

                const auto u = edge[0];
                const auto v = edge[1];
                const auto strength = edge[2];

                if (strength >= stability) {
                    uf.unionSets(u, v);
                } else if (2 * strength >= stability) {
                    upgrade.emplace_back(u, v);
                }
            }

            int remainingUpgrades = k;
            for (const auto& [u, v] : upgrade) {
                if (uf.areConnected(u, v)) {
                    continue;
                }
                if (remainingUpgrades == 0) {
                    return false;
                }
                uf.unionSets(u, v);
                --remainingUpgrades;
            }

            if (uf.getNumComponents() == 1) {
                return true;
            }
            return false;
        };

        int right = 0;
        for (const auto& edge : edges) {
            right = max(right, edge[2]);
        }
        right *= 2;
        int left = -1;
        while (left < right) {
            int m = left + (right - left + 1) / 2;
            if (check(m)) {
                left = m;
            } else {
                right = m - 1;
            }
        }

        return left;
    }
};
