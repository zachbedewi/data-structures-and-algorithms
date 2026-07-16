enum class State { Unvisited, Visiting, Safe, Unsafe };

class Solution {
  public:
    vector<int> eventualSafeNodes(vector<vector<int>> &graph) {
        vector<State> state(graph.size(), State::Unvisited);

        auto dfs = [&](this auto &&self, auto const &u) -> bool {
            if (state[u] == State::Safe)
                return true;
            if (state[u] == State::Unsafe)
                return false;
            if (state[u] == State::Visiting)
                return false;

            state[u] = State::Visiting;
            for (auto const &v : graph[u]) {
                if (!self(v)) {
                    state[u] = State::Unsafe;
                    return false;
                }
            }
            state[u] = State::Safe;
            return true;
        };

        vector<int> res{};
        for (auto i{0uz}; i < graph.size(); ++i) {
            if (dfs(i)) {
                res.push_back(i);
            }
        }

        return res;
    }
};
