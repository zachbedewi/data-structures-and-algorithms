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
public:
    int maxDepth(TreeNode* root) {
        stack<pair<TreeNode*, int>> s;
        s.push({root, 1});
        int maxDepth = 0;

        while (!s.empty()) {
            auto p = s.top();
            s.pop();
            TreeNode* node = p.first;
            int currDepth = p.second;

            if (node) {
                maxDepth = max(maxDepth, currDepth);
                s.push({node->left, currDepth + 1});
                s.push({node->right, currDepth + 1});
            }
        }

        return maxDepth;
    }
};
