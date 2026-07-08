class Solution {
  public:
    vector<int> survivedRobotsHealths(vector<int> &positions,
                                      vector<int> &healths, string directions) {
        vector<vector<int>> robots;
        for (int i = 0; i < positions.size(); ++i) {
            robots.push_back({positions[i], healths[i], directions[i], i});
        }

        ranges::sort(robots);

        vector<vector<int>> st;
        for (auto &robot : robots) {
            if (robot[2] == 'R' || st.empty() || st.back()[2] == 'L') {
                st.push_back(robot);
            } else if (robot[2] == 'L') {
                bool shouldAdd = true;
                while (!st.empty() && st.back()[2] == 'R' && shouldAdd) {
                    const int prevHealth = st.back()[1];
                    if (robot[1] > prevHealth) {
                        st.pop_back();
                        --robot[1];
                    } else if (robot[1] < prevHealth) {
                        --st.back()[1];
                        shouldAdd = false;
                    } else {
                        st.pop_back();
                        shouldAdd = false;
                    }
                }

                if (shouldAdd) {
                    st.push_back(robot);
                }
            }
        }

        ranges::sort(st, [](auto &a, auto &b) { return a[3] < b[3]; });

        vector<int> res;
        for (const auto &robot : st) {
            res.push_back(robot[1]);
        }

        return res;
    }
};
