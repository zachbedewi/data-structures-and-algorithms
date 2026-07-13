class Solution {
  public:
    bool pyramidTransition(string bottom, vector<string> &allowed) {
        unordered_map<string, vector<char>> graph;
        for (auto const &pattern : allowed) {
            graph[pattern.substr(0, 2)].push_back(pattern[2]);
        }
        unordered_map<string, bool> memo{};
        return backtrack(bottom, graph, memo, "", 0);
    }

  private:
    bool backtrack(string const &bottom,
                   unordered_map<string, vector<char>> const &graph,
                   unordered_map<string, bool> &memo, string nextLevel, int i) {
        if (bottom.length() == 1)
            return true;
        if (i == 0 && memo.contains(bottom))
            return memo[bottom];

        if (i == bottom.length() - 1) {
            return memo[bottom] = backtrack(nextLevel, graph, memo, "", 0);
        }

        auto const &key = bottom.substr(i, 2);
        auto const it = graph.find(key);
        if (it == graph.end()) {
            if (i == 0)
                memo[bottom] = false;
            return false;
        }

        for (auto const &option : it->second) {
            nextLevel.push_back(option);
            if (backtrack(bottom, graph, memo, nextLevel, i + 1))
                return true;
            nextLevel.pop_back();
        }

        if (i == 0)
            memo[bottom] = false;
        return false;
    }
};
