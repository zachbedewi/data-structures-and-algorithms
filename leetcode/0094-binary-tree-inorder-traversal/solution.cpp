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
    vector<int> inorderTraversal(TreeNode *root) {
        std::vector<int> res;
        traverse(root, res);
        return res;
    }

  private:
    auto traverse(TreeNode const *root, std::vector<int> &out) -> void {
        if (!root) {
            return;
        }

        traverse(root->left, out);
        out.emplace_back(root->val);
        traverse(root->right, out);
    }
};
