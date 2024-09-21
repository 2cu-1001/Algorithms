#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll N, K, ansP, ansQ, d[1<<16][110], powTen[100];
vector<string> v;
vector<ll> r;
ll EEA(ll a, ll b)
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
    return r0;
}
ll DFS(ll used, ll preRemainder)
{
    if (used == (1 << N) - 1) return (preRemainder == 0 ? 1 : 0);

    ll& ret = d[used][preRemainder];
    if (ret != -1) return ret;

    ret = 0;
    for (ll i = 0; i < N; i++) {
        if (used & (1 << i)) continue;
        ll nxtUsed = used | (1 << i);
        ll nxtRemainder = (powTen[v[i].length()] * preRemainder + r[i]) % K;
        ll res = DFS(nxtUsed, nxtRemainder);
        ret += res;
    }
    
    return ret;
}
ll getRemainder(string s)
{
    ll ret = 0;
    for (int i : s) {
        i -= '0'; ret = (ret * 10 + i) % K;
    }
    return ret;
}
void solve()
{
    powTen[0] = 1;
    for (int i = 1; i <= 60; i++) powTen[i] = (powTen[i - 1] * 10) % K;
    for (auto s : v) r.push_back(getRemainder(s));
    memset(d, -1, sizeof(d));

    ansP = DFS(0, 0);
    ansQ = 1;
    for (ll i = 1; i <= N; i++) ansQ *= i;
    

    if (ansP == 0) {
        cout << "0/1"; return;
    }
    else {
        ll GCD = EEA(ansP, ansQ);
        if (ansP / GCD != 0) ansP /= GCD;
        if (ansQ / GCD != 0) ansQ /= GCD;
        cout << ansP << "/" << ansQ;
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 1; i <= N; i++) {
        string s; cin >> s; v.push_back(s);
    }
    cin >> K;
    solve();
}