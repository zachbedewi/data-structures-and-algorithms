/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
  public:
    vector<int> treeQueries(TreeNode *root, vector<int> &queries) {
        unordered_map<int, int> depths;
        unordered_map<int, int> heights;
        vector<array<int, 2>> best;

        auto dfs = [&](this auto self, TreeNode *node, int depth = 0) -> int {
            if (!node) {
                return -1;
            }

            depths[node->val] = depth;
            auto height = 1 + max(self(node->left, depth + 1),
                                  self(node->right, depth + 1));
            heights[node->val] = height;

            if (best.size() <= static_cast<size_t>(depth)) {
                best.resize(depth + 1, {-1, -1});
            }

            if (height > best[depth][0]) {
                best[depth][1] = best[depth][0];
                best[depth][0] = height;
            } else if (height > best[depth][1]) {
                best[depth][1] = height;
            }
            return height;
        }(root);

        transform(begin(queries), end(queries), begin(queries), [&](int q) {
            int depth = depths[q];
            int height =
                best[depth][0] == heights[q] ? best[depth][1] : best[depth][0];
            return depth + height;
        });
        return queries;
    }
};
