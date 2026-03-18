class Solution {
public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        vector<int> frequency = getFrequencies(nums);
        vector<vector<bool>> validDistribution = getValidDistribution(frequency, quantity);

        const int n = frequency.size();
        const int m = quantity.size();
        const int maxMask = 1 << m;
        vector<vector<bool>> dp(n + 1, vector<bool>(maxMask));
        dp[n][maxMask - 1] = true;

        for (int i = n - 1; i >= 0; --i) {
            for (int mask = 0; mask < maxMask; ++mask) {
                dp[i][mask] = dp[i + 1][mask];
                const int available = ~mask & (maxMask - 1);
                for (int submask = available; submask > 0; submask = (submask - 1) & available) {
                    if (validDistribution[i][submask]) {
                        dp[i][mask] = dp[i][mask] || dp[i + 1][mask | submask];
                    }
                }
            }
        }

        return dp[0][0];
    }

private:
    vector<int> getFrequencies(const vector<int>& nums) {
        unordered_map<int, int> mp;
        for (const auto& num : nums) {
            ++mp[num];
        }

        vector<int> frequencies;
        for (const auto& [_, frequency] : mp) {
            frequencies.push_back(frequency);
        }
        return frequencies;
    }

    vector<vector<bool>> getValidDistribution(const vector<int>& frequency, const vector<int>& quantity) {
        const int maxMask = 1 << quantity.size();
        vector<vector<bool>> validDistribution(frequency.size(), vector<bool>(maxMask));

        for (int i = 0; i < frequency.size(); ++i) {
            for (int mask = 0; mask < maxMask; ++mask) {
                if (frequency[i] >= getQuantitySum(quantity, mask)) {
                    validDistribution[i][mask] = true;
                }
            }
        }

        return validDistribution;
    }

    int getQuantitySum(const vector<int>& quantity, int mask) {
        int sum = 0;
        for (int i = 0; i < quantity.size(); ++i) {
            if ((mask >> i) & 1) {
                sum += quantity[i];
            }
        }
        return sum;
    }
};
