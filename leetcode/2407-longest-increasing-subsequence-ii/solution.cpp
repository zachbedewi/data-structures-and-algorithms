class SegmentTree {
public:
    SegmentTree(int maxValue) : size(maxValue + 1), tree(4 * (maxValue + 1), 0) {}

    int query(int l, int r) { return query(0, 0, size - 1, l, r); }

    void update(int index, int value) { update(0, 0, size - 1, index, value); }

private:
    vector<int> tree;
    int size;

    int query(int v, int l, int r, int tl, int tr) {
        if (tr < l || tl > r) {
            return 0;
        }

        if (tl <= l && r <= tr) {
            return tree[v];
        }

        int mid = (l + r) / 2;
        return max(query(2 * v + 1, l, mid, tl, tr),
                   query(2 * v + 2, mid + 1, r, tl, tr));
    }

    void update(int v, int l, int r, int index, int value) {
        if (l == r) {
            tree[v] = max(tree[v], value);
            return;
        }

        int mid = (l + r) / 2;
        if (index <= mid) {
            update(2 * v + 1, l, mid, index, value);
        } else {
            update(2 * v + 2, mid + 1, r, index, value);
        }
        tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
    }
};

class Solution {
public:
    int lengthOfLIS(vector<int>& nums, int k) {
        SegmentTree tree(ranges::max(nums));
        int maxLength = 1;

        for (const int num : nums) {
            const int left = max(0, num - k);
            const int right = num - 1;
            const int currLength = 1 + tree.query(left, right);
            tree.update(num, currLength);
            maxLength = max(maxLength, currLength);
        }

        return maxLength;
    }
};
