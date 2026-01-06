class Solution {
public:
    long long minMoves(vector<int>& balance) {
        const int n = balance.size();
        long long sum = 0;
        int j = -1;

        for (int i = 0; i < n; ++i) {
            sum += balance[i];
            if (balance[i] < 0) {
                j = i;
            }
        }

        if (j == -1) {
            return 0;
        }
        if (sum < 0) {
            return -1;
        }

        long long ans = 0;
        for (int d = 1; balance[j] < 0; ++d) {
            long long availableBalance = balance[(j + d) % n] + balance[(j + n - d) % n];
            ans += min((long long) abs(balance[j]), availableBalance) * d;
            balance[j] += availableBalance;
        }
        return ans;
    }
};
