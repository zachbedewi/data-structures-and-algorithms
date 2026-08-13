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

    string s;
    cin >> s;

    vector<int> pre(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        pre[i + 1] = pre[i] ^ a[i];
    }

    int xr[2] = {0, 0};
    for (int i = 0; i < n; ++i) {
        xr[s[i] - '0'] ^= a[i];
    }

    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            cin >> l >> r;

            // Flipping s[i] in [l, r] moves the range's 0 elements into
            // group 1 and vice versa
            // Since a group loses its share of the range and gains
            // the other's, and range0 ^ range1 = x:
            // xr[g] = xr[g] ^ range_g ^ range{1 - g} = xr[g] ^ x
            int x = pre[r] ^ pre[l - 1];
            xr[0] ^= x;
            xr[1] ^= x;
        } else {
            int g;
            cin >> g;
            cout << xr[g] << ' ';
        }
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
