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
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int x{INT_MAX};
    int y{INT_MAX};
    int res{0};

    for (auto const num : a) {
        // if (x > y) {
        //     swap(x, y);
        // }

        if (num <= x) {
            x = num;
        } else if (num <= y) {
            y = num;
        } else {
            ++res;
            x = num;
        }
    }

    cout << res << "\n";

    // for (int i = 0;)

    //     vector<int> S, T;
    // int totalPenalty{n};

    // for (int i = 0; i < n; ++i) {
    //     if (S.empty() || a[i] <= S.back()) {
    //         S.push_back(a[i]);
    //         --totalPenalty;
    //     } else if (T.empty() || a[i] <= T.back()) {
    //         T.push_back(a[i]);
    //         --totalPenalty;
    //     } else {
    //         T.push_back(a[i]);
    //     }
    // }

    // cout << totalPenalty << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t; // delete this line for single-test-case problems
    while (t--)
        solve();
}
