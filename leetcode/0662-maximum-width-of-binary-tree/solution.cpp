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
    int widthOfBinaryTree(TreeNode* root) {
        queue<pair<TreeNode*, uint32_t>> q{{{root, 0}}};

        int res = 0;
        while (!q.empty()) {
            const uint32_t offset = q.front().second;
            res = max(res, static_cast<int>(q.back().second - q.front().second + 1));
            for (int sz = q.size(); sz > 0; --sz) {
                auto [node, index] = q.front();
                q.pop();
                index -= offset;

                if (node->left) {
                    q.emplace(node->left, 2 * index);
                }
                if (node->right) {
                    q.emplace(node->right, 2 * index + 1);
                }
            }
        }

        return res;
    }
};
