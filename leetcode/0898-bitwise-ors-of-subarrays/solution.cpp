class Solution {
  public:
    int subarrayBitwiseORs(vector<int> &arr) {
        unordered_set<int> res;
        unordered_set<int> curr;
        unordered_set<int> prev;

        for (auto const num : arr) {
            curr.insert(num);
            for (auto const i : prev) {
                curr.insert(i | num);
            }

            res.insert(curr.begin(), curr.end());
            prev = curr;
            curr.clear();
        }

        return res.size();
    }
};
