#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

#ifdef LOCAL
#define dbg(...) (cerr << "[" << #__VA_ARGS__ << "] = ", dbg_out(__VA_ARGS__))
template <class T> void dbg_out(const T &x) { cerr << x << '\n'; }
template <class T, class... R> void dbg_out(const T &x, const R &...r) {
    cerr << x << ", ";
    dbg_out(r...);
}
#else
#define dbg(...)
#endif

void solve() {
    int n;
    cin >> n;

    vector<int> teaAmounts(n);
    for (auto &x : teaAmounts) {
        cin >> x;
    }

    vector<int> tasterAmounts(n);
    for (auto &x : tasterAmounts) {
        cin >> x;
    }

    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] + tasterAmounts[i];
    }

    vector<long long> fullDrinkCount(n + 2, 0);
    vector<long long> partialSipAmount(n, 0);

    for (int i = 0; i < n; ++i) {
        // want to find it such that *it - prefix[i] > teaAmount[i]
        // *it > teaAmount[i] + prefix[i]
        auto last = std::upper_bound(prefix.begin() + i, prefix.end(),
                                     prefix[i] + teaAmounts[i]);

        fullDrinkCount[i] += 1;
        if (last != prefix.end()) {
            auto j = std::distance(prefix.begin(), last);
            fullDrinkCount[j - 1] -= 1;
            partialSipAmount[j - 1] +=
                teaAmounts[i] - (prefix[j - 1] - prefix[i]);
        } else {
            fullDrinkCount[n] -= 1;
        }
    }

    long long curr = 0;
    for (int i = 0; i < n; ++i) {
        curr += fullDrinkCount[i];
        cout << partialSipAmount[i] + curr * tasterAmounts[i] << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t; // delete this line for single-test-case problems
    while (t--)
        solve();
}
