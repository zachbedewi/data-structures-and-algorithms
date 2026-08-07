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

    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    ll res{0};
    for (int i = 1; i <= 60; ++i) {
        unordered_set<long long> distinctVals;
        long long k = 1LL << i;

        for (int id = 0; id < n; ++id) {
            distinctVals.insert(a[id] % k);
        }
        if (distinctVals.size() == 2) {
            res = k;
            break;
        }
    }

    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t; // delete this line for single-test-case problems
    while (t--)
        solve();
}
