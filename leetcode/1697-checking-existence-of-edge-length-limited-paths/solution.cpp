class UnionFind {
public:

    UnionFind(int n) : parent(n), size(n) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int u) {
        if (u == parent[u]) {
            return u;
        }
        return parent[u] = find(parent[u]);
    }

    void unionSets(int u, int v) {
        u = find(u);
        v = find(v);
        if (u != v) {
            if (size[u] < size[v]) {
                swap(u, v);
            }
            parent[v] = u;
            size[u] += size[v];
        }
    }

private:
    vector<int> parent;
    vector<int> size;
};

class Solution {
public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        for (int i = 0; i < queries.size(); ++i) {
            queries[i].push_back(i);
        }

        ranges::sort(queries, [](const auto& a, const auto& b) {
            return a[2] < b [2];
        });
        ranges::sort(edgeList, [](const auto& a, const auto& b) {
            return a.back() < b.back();
        });

        int i = 0;
        UnionFind uf(n);
        vector<bool> res(queries.size());
        for (const auto& query : queries) {
            for (; i < edgeList.size() && edgeList[i].back() < query[2]; ++i) {
                uf.unionSets(edgeList[i][0], edgeList[i][1]);
            }

            const auto start = query[0];
            const auto end = query[1];
            res[query.back()] = uf.find(start) == uf.find(end);
        }

        return res;
    }
};
