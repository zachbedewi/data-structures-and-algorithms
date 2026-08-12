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

    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }

    // keep[i] := Max number of elements kept from suffix i
    vector<int> keep(n + 1, 0);
    for (int i{n - 1}; i >= 0; --i) {
        keep[i] = keep[i + 1];
        if (a[i] <= n - i - 1) {
            keep[i] = max(keep[i], a[i] + 1 + keep[i + a[i] + 1]);
        }
    }

    cout << n - keep[0] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t; // delete this line for single-test-case problems
    while (t--)
        solve();
}
