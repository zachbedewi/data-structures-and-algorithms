class Solution {
  public:
    vector<int> sequentialDigits(int low, int high) {
        string const sequential{"123456789"};

        auto const lowString = to_string(low);
        auto const highString = to_string(high);

        vector<int> res{};

        for (int i = lowString.length(); i <= highString.length(); ++i) {
            for (int j = 0; j <= 9 - i; ++j) {
                string const option = sequential.substr(j, i);
                auto const num = stoi(option);
                if (low <= num && num <= high) {
                    res.push_back(num);
                }
            }
        }

        return res;
    }
};
