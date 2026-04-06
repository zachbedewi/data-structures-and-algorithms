class Solution {
public:
    long long minimumMoney(vector<vector<int>>& transactions) {
        // losses = sum_{i = 0}^{n} max(0, transactions[i][0] - transactions[i][1])
        // Therefore, money needed for the last transaction:
        // if cost > cashback => losses - (cost - cashback) + cost = losses + cashback
        // if cost < cashback => losses + cost
        // => maxFinalTransactionCost = max_{i = 0}^{n} (maxFinalTransactionCost, min(transactions[i][0], transactions[i][1]))

        long long losses = 0;
        int maxFinalTransactionCost = 0;
        for (const auto& transaction : transactions) {
            const int cost = transaction[0];
            const int cashback = transaction[1];
            losses += max(0, cost - cashback);
            maxFinalTransactionCost = max(maxFinalTransactionCost, min(cost, cashback));
        }

        return losses + maxFinalTransactionCost;
    }
};
