struct TrieNode {
    unordered_map<int, shared_ptr<TrieNode>> children;
    int count;
};

class Trie {
    shared_ptr<TrieNode> root = make_shared<TrieNode>();

    int hash(char prefix, char suffix) {
        return 26 * (prefix - 'a') + (suffix - 'a');
    }

public:

    int insert(const string& word) {
        const int n = word.size();
        shared_ptr<TrieNode> node = root;
        int count = 0;
        for (int i = 0; i < n; ++i) {
            const int h = hash(word[i], word[n - 1 - i]);
            if (node->children[h] == nullptr) {
                node->children[h] = make_shared<TrieNode>();
            }
            node = node->children[h];
            count += node->count;
        }
        ++node->count;
        return count;
    }
};

class Solution {
public:
    long long countPrefixSuffixPairs(vector<string>& words) {
        Trie t;
        long long res = 0;

        for (const auto& word : words) {
            res += t.insert(word);
        }

        return res;
    }
};
