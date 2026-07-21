class Solution {
  public:
    string crackSafe(int n, int k) {
        unordered_set<string> visited{};
        string start(n - 1, '0');

        string res{};
        dfs(start, visited, k, res);

        res += start;
        return res;
    }

  private:
    void dfs(const string &node, unordered_set<string> &visited, int k,
             string &res) {
        for (int x = 0; x < k; ++x) {
            string neighbor = node + to_string(x);
            if (!visited.contains(neighbor)) {
                visited.insert(neighbor);
                dfs(neighbor.substr(1), visited, k, res);
                res += to_string(x);
            }
        }
    }
};
