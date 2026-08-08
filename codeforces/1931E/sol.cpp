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
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int totalDigits{};
    vector<int> trailingZeros(n);

    for (int i = 0; i < n; ++i) {
        while (a[i] % 10 == 0) {
            ++trailingZeros[i];
            a[i] /= 10;
            ++totalDigits;
        }

        while (a[i] > 0) {
            a[i] /= 10;
            ++totalDigits;
        }
    }

    sort(trailingZeros.begin(), trailingZeros.end(), greater<>{});

    for (int i = 0; i < n; i += 2) {
        totalDigits -= trailingZeros[i];
    }
    if (totalDigits > m) {
        cout << "Sasha\n";
    } else {
        cout << "Anna\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t; // delete this line for single-test-case problems
    while (t--)
        solve();
}
