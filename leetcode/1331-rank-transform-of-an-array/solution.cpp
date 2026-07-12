class Solution {
  public:
    vector<int> arrayRankTransform(vector<int> &arr) {
        auto s = arr;
        ranges::sort(s);
        s.erase(unique(s.begin(), s.end()), s.end());

        vector<int> res(arr.size(), 0);
        for (auto const [i, n] : arr | views::enumerate) {
            res[i] = lower_bound(s.begin(), s.end(), n) - s.begin() + 1;
        }

        return res;
    }
};
