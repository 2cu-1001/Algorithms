#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll N, K, ans;
bool isOk(ll mid)
{
    ll cnt = 0; 
    for (int i = 1; i <= N; i++)
        cnt += min(mid / i, N);
    if (cnt >= K) return true;
    return false;
}
void solve()
{
    ll st, ed, mid;
    st = 1; ed = N * N;
    while (st <= ed) {
        mid = (st + ed) / 2;
        if (isOk(mid)) {
            ed = mid - 1;
            ans = mid;
        }
        else st = mid + 1;
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N >> K;
    solve();
    cout << ans;
    return 0;
}