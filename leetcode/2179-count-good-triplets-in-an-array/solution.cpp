class SegmentTree {
    vector<int> tree;
    size_t n;

    void build(vector<int> const &v, size_t idx, size_t start, size_t end) {
        if (start == end) {
            tree[idx] = v[start];
            return;
        }
        auto const m = start + (end - start) / 2;
        build(v, 2 * idx + 1, start, m);
        build(v, 2 * idx + 2, m + 1, end);
        tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    }

    void update(size_t idx, int val, size_t curr, size_t start, size_t end) {
        if (start == end) {
            tree[curr] = val;
            return;
        }
        auto const m = start + (end - start) / 2;
        if (idx <= m) {
            update(idx, val, 2 * curr + 1, start, m);
        } else {
            update(idx, val, 2 * curr + 2, m + 1, end);
        }
        tree[curr] = tree[2 * curr + 1] + tree[2 * curr + 2];
    }

    int query(size_t l, size_t r, size_t curr, size_t start, size_t end) {
        if (l > end || r < start) {
            return 0;
        }

        if (l <= start && end <= r) {
            return tree[curr];
        }

        auto const m = start + (end - start) / 2;
        return query(l, r, 2 * curr + 1, start, m) +
               query(l, r, 2 * curr + 2, m + 1, end);
    }

  public:
    explicit SegmentTree(vector<int> const &v)
        : n{v.size()}, tree(4 * v.size(), 0) {
        build(v, 0, 0, n - 1);
    }

    void update(size_t idx, int val) { update(idx, val, 0, 0, n - 1); }

    int query(size_t l, size_t r) { return query(l, r, 0, 0, n - 1); }
};

class Solution {
  public:
    long long goodTriplets(vector<int> &nums1, vector<int> &nums2) {
        auto const n = nums1.size();
        unordered_map<int, int> valToIdx;

        for (int i = 0; i < n; ++i) {
            valToIdx[nums1[i]] = i + 1;
        }
        for (auto &num : nums2) {
            num = valToIdx[num];
        }

        vector<int> leftArr(n, 0);
        vector<int> rightArr(n, 1);
        SegmentTree leftTree{leftArr};
        SegmentTree rightTree{rightArr};

        leftTree.update(nums2[0] - 1, 1);
        rightTree.update(nums2[0] - 1, 0);

        auto res{0LL};
        for (auto i{1uz}; i < n - 1; ++i) {
            auto idx = nums2[i];

            rightTree.update(idx - 1, 0);

            auto left = (idx >= 2) ? leftTree.query(0, idx - 2) : 0;
            auto right = rightTree.query(idx, n - 1);

            res += static_cast<long long>(left) * right;
            leftTree.update(idx - 1, 1);
        }
        return res;
    }
};
