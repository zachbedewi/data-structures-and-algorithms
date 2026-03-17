class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        vector<pair<int, int>> positionAndSpeed;
        for (int i = 0; i < position.size(); i++) {
            positionAndSpeed.push_back({position[i], speed[i]});
        }

        sort(positionAndSpeed.begin(), positionAndSpeed.end(), greater<pair<int, int>>());

        stack<double> st;
        for (auto& p : positionAndSpeed) {
            double t = (double)(target - p.first) / p.second;
            if (st.empty() || t > st.top()) {
                st.push(t);
            }
        }

        return st.size();
    }
};
