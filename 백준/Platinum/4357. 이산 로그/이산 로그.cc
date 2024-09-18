#include <bits/stdc++.h>
#define ll long long
using namespace std;
unordered_map<ll, ll> h;
ll P, B, N, m, a1, a2, inverse;
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
    return (s0 < 0 ? s0 + b : s0);
}
void solve()
{
    m = (ll)ceil(sqrt(P - 1));
    inverse = EEA(B, P);
    // L = i * m + j
    ll curPow = 1;
    for (int j = 0; j <= m; j++) {
        ll cur = (N * curPow) % P;
        h.insert({ cur, j });
        curPow = (curPow * inverse) % P;
    }

    ll mPow = 1;
    for (int i = 1; i <= m; i++) mPow = (mPow * B) % P;

    curPow = 1;
    for (int i = 0; i <= m; i++) {
        auto it = h.find(curPow);
        if (it != h.end()) {
            cout << ((i * m) % P + it->second) % P << "\n";
            return;
        }
        curPow = (curPow * mPow) % P;
    }

    cout << "no solution\n";
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    while (cin >> P >> B >> N) {
        h.clear(); solve();
    }
}
