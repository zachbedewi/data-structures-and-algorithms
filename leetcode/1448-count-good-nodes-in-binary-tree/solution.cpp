/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    int dfs(TreeNode* root, int maxAncestorVal) {
        if (!root) {
            return 0;
        }

        int goodCount = 0;
        if (root->val >= maxAncestorVal) {
            goodCount++;
        }
        maxAncestorVal = max(maxAncestorVal, root->val);

        return goodCount + dfs(root->left, maxAncestorVal) + dfs(root->right, maxAncestorVal);
    }
public:
    int goodNodes(TreeNode* root) {
        int res = 0;
        queue<pair<TreeNode*, int>> q;
        q.push({root, INT_MIN});

        while (!q.empty()) {
            auto [node, maxVal] = q.front();
            q.pop();

            if (node->val >= maxVal) {
                res++;
            }
            if (node->right) {
                q.push({node->right, max(maxVal, node->val)});
            }
            if (node->left) {
                q.push({node->left, max(maxVal, node->val)});
            }
        }

        return res;
    }
};
