#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll N, A;
pair<ll, ll> EEA(ll a, ll b)
{
    ll r0 = a, r1 = b, s0 = 1, s1 = 0, 
        t0 = 0, t1 = 1, tmp = 0, q = 0;
    while (r1) {
        q = r0 / r1;
        tmp = r0;
        r0 = r1;
        r1 = tmp - r1 * q;
        tmp = s0;
        s0 = s1;
        s1 = tmp - s1 * q;
        tmp = t0;
        t0 = t1;
        t1 = tmp - t1 * q;
    }
    return {(s0 < 0 ? s0 + b : s0), r0};
}
void solve()
{
    auto ans = EEA(A, N);
    cout << N - A << " " << (ans.second == 1 ? ans.first : -1);
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N >> A;
    solve();
}
