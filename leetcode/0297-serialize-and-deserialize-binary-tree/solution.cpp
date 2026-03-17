/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) {
            return "n";
        }
        string serialized;
        queue<TreeNode*> q{{root}};

        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            if (!node) {
                serialized += "n,";
            } else {
                serialized += to_string(node->val) + ",";
                q.push(node->left);
                q.push(node->right);
            }
        }

        return serialized;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        stringstream stream(data);
        string node;
        getline(stream, node, ',');
        if (node == "n") {
            return nullptr;
        }
        TreeNode* root = new TreeNode(stoi(node));
        queue<TreeNode*> q {{root}};

        while (getline(stream, node, ',')) {
            TreeNode* curr = q.front();
            q.pop();

            if (node != "n") {
                curr->left = new TreeNode(stoi(node));
                q.push(curr->left);
            }

            getline(stream, node, ',');
            if (node != "n") {
                curr->right = new TreeNode(stoi(node));
                q.push(curr->right);
            }
        }

        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
