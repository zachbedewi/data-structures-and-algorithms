class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int l {1}, r {*max_element(piles.begin(), piles.end())}, minK {r};

        while (l <= r) {
            int m = l + (r - l) / 2;

            long timeToEatAll {};
            for (int pile : piles) {
                timeToEatAll += ceil(static_cast<double>(pile) / m);
            }

            // Trying to find the lower bound, so we use equals here
            if (timeToEatAll <= h) {
                minK = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }

        return minK;
    }
};
