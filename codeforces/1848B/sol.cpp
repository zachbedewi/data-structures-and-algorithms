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
    int n, k;
    cin >> n >> k;
    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    vector<int> last(k, -1);
    vector<int> max1(k), max2(k);

    for (int i = 0; i < n; ++i) {
        int step = i - last[c[i] - 1];
        if (step > max1[c[i] - 1] - 1) {
            max2[c[i] - 1] = max1[c[i] - 1];
            max1[c[i] - 1] = step;
        } else if (step > max2[c[i] - 1]) {
            max2[c[i] - 1] = step;
        }
        last[c[i] - 1] = i;
    }

    for (int i = 0; i < k; ++i) {
        int step = n - last[i];
        if (step > max1[i]) {
            max2[i] = max1[i];
            max1[i] = step;
        } else if (step > max2[i]) {
            max2[i] = step;
        }
    }

    int res = 1e9;
    for (int i = 0; i < k; ++i) {
        res = min(res, max((max1[i] + 1) / 2, max2[i]));
    }
    cout << res - 1 << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t; // delete this line for single-test-case problems
    while (t--)
        solve();
}
