class Solution {
public:
    int minimizeSet(int divisor1, int divisor2, int uniqueCnt1,
                    int uniqueCnt2) {
        const long divisorLcm =
            lcm(static_cast<long>(divisor1), static_cast<long>(divisor2));
        long l = 1;
        long r = numeric_limits<int>::max();

        while (l < r) {
            const long m = l + (r - l) / 2;
            if (check(m, divisorLcm, divisor1, divisor2, uniqueCnt1,
                      uniqueCnt2)) {
                r = m;
            } else {
                l = m + 1;
            }
        }

        return l;
    }

private:
    bool check(long m, long divisorLcm, long divisor1, long divisor2,
               long uniqueCnt1, long uniqueCnt2) {
        const bool isCount1Sufficient = (m - m / divisor1) >= uniqueCnt1;
        const bool isCount2Sufficient = (m - m / divisor2) >= uniqueCnt2;
        const bool isTotalCountSufficient = (m - m / divisorLcm) >= uniqueCnt1 + uniqueCnt2;

        return isCount1Sufficient && isCount2Sufficient && isTotalCountSufficient;
    }
};
