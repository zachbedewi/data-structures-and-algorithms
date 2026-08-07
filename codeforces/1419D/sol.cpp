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

vector<int> findMax3(vector<int> const &v) {
    int mx1, mx2, mx3;
    mx1 = mx2 = mx3 = -1;

    for (int i = 0; i < v.size(); ++i) {
        if (mx1 == -1 || v[i] > v[mx1]) {
            mx3 = mx2;
            mx2 = mx1;
            mx1 = i;
        } else if (mx2 == -1 || v[i] > v[mx2]) {
            mx3 = mx2;
            mx2 = i;
        } else if (mx3 == -1 || v[i] > v[mx3]) {
            mx3 = i;
        }
    }

    return {mx1, mx2, mx3};
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    auto res{0};
    for (auto id1 : findMax3(a)) {
        for (auto id2 : findMax3(b)) {
            for (auto id3 : findMax3(c)) {
                if (id1 != id2 && id1 != id3 && id2 != id3) {
                    res = max(res, a[id1] + b[id2] + c[id3]);
                }
            }
        }
    }
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t; // delete this line for single-test-case problems
    while (t--)
        solve();
}
