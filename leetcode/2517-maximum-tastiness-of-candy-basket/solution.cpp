class Solution {
public:
    int maximumTastiness(vector<int>& price, int k) {
        const int n = price.size();
        ranges::sort(price);
        int l = 0;
        int r = price.back() - price.front();

        while (l < r) {
            int m = 1 + l + (r - l) / 2;
            if (check(m, price, k)) {
                l = m;
            } else {
                r = m - 1;
            }
        }

        return l;
    }

private:
    bool check(int target, vector<int>& price, int k) {
        int prev = price[0];
        int count = 1;

        for (int i = 1; i < price.size(); ++i) {
            if (price[i] - prev >= target) {
                if (++count == k) {
                    return true;
                };
                prev = price[i];
            }
        }

        return false;
    }
};
