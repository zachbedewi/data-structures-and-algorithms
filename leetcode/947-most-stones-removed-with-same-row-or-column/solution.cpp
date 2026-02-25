class UnionFind {
public:

    UnionFind(int n) : parent{}, count(0) { }

    int find(int v) {
        if (!parent.count(v)) {
            parent[v] = v;
            ++count;
        }
        if (v != parent[v]) {
            parent[v] = find(parent[v]);
        }
        return parent[v];
    }

    void unionSets(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            parent[a] = b;
            --count;
        }
    }

    int getCount() {
        return count;
    }

private:
    unordered_map<int, int> parent;
    int count;
};

class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        const int n = stones.size();
        UnionFind uf(n);

        for (int i = 0; i < stones.size(); ++i) {
            // Use ~ to make sure that the column values are unique when compared to row values
            uf.unionSets(stones[i][0], ~stones[i][1]);
        }
        return stones.size() - uf.getCount();
    }
};
