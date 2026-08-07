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

ll sum(ll a, ll b) { return ((b - a + 1) * (a + b)) / 2; }

void solve() {
    ll n, x, y;
    cin >> n >> x >> y;

    ll lcmxy = lcm(x, y);
    ll large = n / x - n / lcmxy;
    ll small = n / y - n / lcmxy;

    auto score = sum(n - large + 1, n) - sum(1LL, small);
    cout << score << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t; // delete this line for single-test-case problems
    while (t--)
        solve();
}
