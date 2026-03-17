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
    bool isValidBST(TreeNode* root) {
        return isValidBst(root, nullptr, nullptr);
    }

private:
    bool isValidBst(TreeNode* root, TreeNode* minNode, TreeNode* maxNode) {
        if (!root) {
            return true;
        }

        if (maxNode && root->val >= maxNode->val) {
            return false;
        }

        if (minNode && root->val <= minNode->val) {
            return false;
        }

        return isValidBst(root->left, minNode, root) &&
            isValidBst(root->right, root, maxNode);
    }
};
