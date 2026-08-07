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

    int bSize = (n * (n - 1)) / 2;

    vector<ll> b(bSize);
    for (int i = 0; i < bSize; ++i) {
        cin >> b[i];
    }
    sort(b.begin(), b.end());
    int expected = n - 1;
    int i = 0;
    while (expected > 0) {
        cout << b[i] << " ";

        i += expected;
        --expected;
    }
    cout << "1000000000\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t; // delete this line for single-test-case problems
    while (t--)
        solve();
}
