class PrefixSumSegmentTree {
  public:
    explicit PrefixSumSegmentTree(int n) : n_(n), nodes_(4 * n) {}

    void set(int pos, int val) { set(1, 0, n_ - 1, pos, val); }

    [[nodiscard]] int findPrefix(int target) const {
        if (target == 0) {
            return -1;
        }
        if (target < nodes_[1].mn || target > nodes_[1].mx) {
            return n_;
        }
        int pref = 0;
        return findPrefix(1, 0, n_ - 1, target, pref);
    }

  private:
    struct Node {
        int sum = 0;
        int mn = 0;
        int mx = 0;
        optional<int> lazy{};
    };

    int n_;
    vector<Node> nodes_;

    void pull(int v) {
        auto &[s, lo, hi, _] = nodes_[v];
        const auto &l = nodes_[2 * v];
        const auto &r = nodes_[2 * v + 1];
        s = l.sum + r.sum;
        lo = min(l.mn, l.sum + r.mn);
        hi = max(l.mx, l.sum + r.mx);
    }

    void applySet(int v, int l, int r, int val) {
        const int len = r - l + 1;
        auto &node = nodes_[v];
        node.sum = val * len;
        if (val == 0) {
            node.mn = 0;
            node.mx = 0;
        } else if (val > 0) {
            node.mn = val;
            node.mx = val * len;
        } else {
            node.mn = val * len;
            node.mx = val;
        }
        node.lazy = val;
    }

    void pushDown(int v, int l, int r) {
        if (!nodes_[v].lazy || l == r) {
            return;
        }
        int mid = (l + r) / 2;
        applySet(2 * v, l, mid, *nodes_[v].lazy);
        applySet(2 * v + 1, mid + 1, r, *nodes_[v].lazy);
        nodes_[v].lazy.reset();
    }

    void set(int v, int l, int r, int pos, int val) {
        if (l == r) {
            applySet(v, l, r, val);
            return;
        }
        pushDown(v, l, r);
        int mid = (l + r) / 2;
        if (pos <= mid) {
            set(2 * v, l, mid, pos, val);
        } else {
            set(2 * v + 1, mid + 1, r, pos, val);
        }
        pull(v);
    }

    [[nodiscard]] int findPrefix(int v, int l, int r, int target,
                                 int &pref) const {
        if (l == r) {
            return (pref + nodes_[v].sum == target) ? l : n_;
        }
        const_cast<PrefixSumSegmentTree *>(this)->pushDown(v, l, r);
        int mid = (l + r) / 2;
        int leftMin = pref + nodes_[2 * v].mn;
        int leftMax = pref + nodes_[2 * v].mx;
        if (target >= leftMin && target <= leftMax) {
            return findPrefix(2 * v, l, mid, target, pref);
        }
        pref += nodes_[2 * v].sum;
        return findPrefix(2 * v + 1, mid + 1, r, target, pref);
    }
};

class Solution {
  public:
    int longestBalanced(vector<int> &nums) {
        const auto n = ssize(nums);
        const int m = *ranges::max_element(nums) + 1;

        PrefixSumSegmentTree tree(n);
        vector<int> lastPos(m, -1);
        int balance = 0;
        int res = 0;

        for (const auto &&[i, num] : nums | views::enumerate) {
            const auto v = num % 2 == 0 ? 1 : -1;

            if (lastPos[num] != -1) {
                tree.set(lastPos[num], 0);
            } else {
                balance += v;
            }

            lastPos[num] = static_cast<int>(i);
            tree.set(static_cast<int>(i), v);

            if (balance == 0) {
                res = max(res, static_cast<int>(i) + 1);
            } else if (int p = tree.findPrefix(balance); p < n) {
                res = max(res, static_cast<int>(i) - p);
            }
        }

        return res;
    }
};
