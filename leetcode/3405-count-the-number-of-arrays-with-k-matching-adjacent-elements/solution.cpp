class Solution {
public:
    int countGoodArrays(int n, int m, int k) {
        const auto [fact, invFact] = getFactAndInvFact(n);
        return m * binPow(m - 1, n - k - 1) % MODULUS * nCk(n - 1, k, fact, invFact) % MODULUS;
    }

private:
    static constexpr int MODULUS = 1'000'000'007;

    long long binPow(long long a, long long b) {
        long long res = 1;
        while (b > 0) {
            if (b & 1) {
                res = (res * a) % MODULUS;
            }
            a = (a * a) % MODULUS;
            b >>= 1;
        }
        return res;
    }

    pair<vector<long long>, vector<long long>> getFactAndInvFact(int n) {
        vector<long long> fact(n + 1);
        vector<long long> invFact(n + 1);
        vector<long long> inv(n + 1);
        fact[0] = invFact[0] = 1;
        inv[0] = inv[1] = 1;
        for (int i = 1; i <= n; ++i) {
            if (i >= 2) {
                inv[i] = MODULUS - MODULUS / i * inv[MODULUS % i] % MODULUS;
            }
            fact[i] = i * fact[i - 1] % MODULUS;
            invFact[i] = invFact[i - 1] * inv[i] % MODULUS;
        }
        return {fact, invFact};
    }

    int nCk(int n, int k, const vector<long long>& fact, const vector<long long>& invFact) {
        return fact[n] * invFact[k] % MODULUS * invFact[n - k] % MODULUS;
    }
};
