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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int preorderIdx {}, inorderIdx {};
        return build(preorder, inorder, preorderIdx, inorderIdx, INT_MAX);
    }

private:
    TreeNode* build(vector<int>& preorder, vector<int>& inorder, int& preorderIdx, int& inorderIdx, int limit) {
        if (preorderIdx >= preorder.size()) {
            return nullptr;
        }
        if (inorder[inorderIdx] == limit) {
            inorderIdx++;
            return nullptr;
        }

        TreeNode* curr = new TreeNode(preorder[preorderIdx++]);
        curr->left = build(preorder, inorder, preorderIdx, inorderIdx, curr->val);
        curr->right = build(preorder, inorder, preorderIdx, inorderIdx, limit);
        return curr;
    }
};
