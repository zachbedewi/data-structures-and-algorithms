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
    int maxPathSum(TreeNode* root) {
        int maxSum = root->val;
        dfs(root, maxSum);
        return maxSum;
    }

private:
    int dfs(TreeNode* root, int& maxSum) {
        if (!root) {
            return 0;
        }

        int leftMax = max(dfs(root->left, maxSum), 0);
        int rightMax = max(dfs(root->right, maxSum), 0);

        maxSum = max(maxSum, root->val + leftMax + rightMax);

        return root->val + max(leftMax, rightMax);
    }
};
