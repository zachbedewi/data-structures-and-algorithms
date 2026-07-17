
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
    int minCameraCover(TreeNode *root) {
        int res = 0;
        if (dfs(root, res) == NO_CAMERA)
            ++res;
        return res;
    }

  private:
    static constexpr int NO_CAMERA{0};
    static constexpr int HAS_CAMERA{1};
    static constexpr int NO_CAMERA_NEEDED{2};

    int dfs(TreeNode *root, int &res) {
        if (!root) {
            return NO_CAMERA_NEEDED;
        }

        auto l = dfs(root->left, res);
        auto r = dfs(root->right, res);

        if (l == NO_CAMERA || r == NO_CAMERA) {
            ++res;
            return HAS_CAMERA;
        } else if (l == HAS_CAMERA || r == HAS_CAMERA) {
            return NO_CAMERA_NEEDED;
        } else {
            return NO_CAMERA;
        }
    }
};
