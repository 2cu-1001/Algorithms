#include <bits/stdc++.h>
using namespace std;
int n, m, k;
void solve()
{
    if (n + 1 < m + k || n > m * k) {
        cout << -1 << "\n"; return;
    }

    int q = n / k, st = 0, ed = 0;
    while (n - q * k + q < m) q--;
    for (int i = 1; i <= q; i++) {
        st = ed + 1; ed += k;
        for (int j = ed; j >= st; j--) cout << j << " ";
    }

    int remain = m - q;
    for (int i = n - remain + 1; i <= n; i++) cout << i << " ";
    for (int i = n - remain; i >= ed + 1; i--) cout << i << " ";
    cout << "\n";
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> k;
    solve();
}