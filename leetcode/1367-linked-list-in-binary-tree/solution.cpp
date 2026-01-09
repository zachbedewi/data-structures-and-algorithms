/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
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
    bool isSubPath(ListNode* head, TreeNode* root) {
        return isSubPathFirstLayer(head, root);
    }

private:

    bool isSubPathFirstLayer(ListNode* head, TreeNode* root) {
        if (head && !root) {
            return false;
        }
        if (checkSubTree(head, root)) {
            return true;
        }
        return isSubPathFirstLayer(head, root->left) || isSubPathFirstLayer(head, root->right);
    }

    bool checkSubTree(ListNode* head, TreeNode* root) {
        if (!head) {
            return true;
        }
        if (!root) {
            return false;
        }
        if (head->val == root->val) {
            return checkSubTree(head->next, root->left) || checkSubTree(head->next, root->right);
        }
        return false;
    }
};
