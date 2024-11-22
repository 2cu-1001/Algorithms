#include <bits/stdc++.h>
#define st first
#define ed second
#define ll long long
#define i128 __int128
using namespace std;
ll T, A, B, C, M, a, b, c, ans;
pair<pair<ll, ll>, ll> EEA(ll m1, ll m2)
{
    //m1 * s0 + m2 * t0 = r0 = GCD(m1, m2)
    ll r0 = m1, r1 = m2, s0 = 1, s1 = 0,
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
    return { {s0, t0}, r0 };
}
ll CRT(ll p, ll q, ll x, ll y, i128 mod)
{
    ll ret, pi, qi;
    pair<pair<ll, ll>, ll> eeaRet = EEA(p, q);
    pi = eeaRet.st.st; qi = eeaRet.st.ed;
    ret = (((i128)x * q) % mod * qi) % mod + (((i128)y * p) % mod * pi) % mod;
    ret = (ret + mod) % mod;
    return ret;
}
void solve()
{
    ll gcdAB = EEA(A, B).ed;
    if (a % gcdAB != b % gcdAB) { cout << -1 << "\n"; return; }
    i128 modAB = (i128)A / gcdAB * B;
    
    ll AB = modAB;
    ll crtAB = CRT(A / gcdAB, B / gcdAB, a, b, modAB);

    ll gcdABC = EEA(AB, C).ed;
    if(crtAB % gcdABC != c % gcdABC) { cout << -1 << "\n"; return; }
    i128 modABC = (i128)AB / gcdABC * C;
    AB /= gcdABC; C /= gcdABC;

    ll ans = CRT(AB, C, crtAB, c, modABC);
    cout << ans << "\n";
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> A >> B >> C >> a >> b >> c;
        solve();
    }
}