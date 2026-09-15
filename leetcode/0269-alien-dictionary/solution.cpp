class Solution {
public:
    string alienOrder(vector<string>& words) {
        // topological sort
        std::unordered_map<char, int> indegree;
        std::unordered_map<char, std::unordered_set<char>> graph;

        for (auto const& word : words) {
            for (auto const c : word) {
                indegree[c] = 0;
            }
        }

        for (auto i : std::views::iota(0uz, words.size() - 1)) {
            auto const& word1{words[i]};
            auto const& word2{words[i + 1]};
            if (word1.length() > word2.length() && word1.substr(0, word2.length()) == word2) {
                return "";
            }

            for (auto j : std::views::iota(0uz, std::min(word1.length(), word2.length()))) {
                if (word1[j] != word2[j]) {
                    if (graph[word1[j]].insert(word2[j]).second) {
                        ++indegree[word2[j]];
                    }
                    break;
                }
            }
        }

        std::string res = "";
        std::queue<char> q;
        for (auto const [c, in] : indegree) {
            if (in == 0) {
                q.push(c);
            }
        }

        while (!q.empty()) {
            auto const c = q.front();
            q.pop();

            res += c;
            for (auto const next : graph[c]) {
                --indegree[next];
                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }

        if (res.length() < indegree.size()) {
            return "";
        }

        return res;
    }
};
