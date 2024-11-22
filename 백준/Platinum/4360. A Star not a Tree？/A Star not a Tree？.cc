#include <bits/stdc++.h>
#define ld long double
#define ll long long
using namespace std;
typedef struct {
    ld x, y;
}P;
int N;
ld learningRate = 1000, delta = 0.9999;
P c, grad;
vector<P> p;
ld getDist(P p1, P p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
void getGrad()
{
    P retGrad = { 0, 0 };

    for (int i = 0; i < N; i++) {
        ld curDist = getDist(c, p[i]);
        if (curDist == 0) continue;
        retGrad.x += (c.x - p[i].x) / curDist;
        retGrad.y += (c.y - p[i].y) / curDist;
    }

    grad = retGrad;
}
ll getAns()
{
    ld ans = 0;
    for (auto i : p) ans += getDist(c, i);
    return (ll)round(ans);
}
void solve()
{
    c = { 0, 0 };
    for (auto i : p) { c.x += i.x; c.y += i.y; }
    c.x /= (ld)N; c.y /= (ld)N;

    int iterCnt = 0;
    while (iterCnt < 500000) {
        getGrad();
        c = { c.x - learningRate * grad.x, c.y - learningRate * grad.y };
        learningRate *= delta;
        iterCnt++;
    }

    cout << getAns();
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N;
    for (int i = 1; i <= N; i++) {
        P tmpP; cin >> tmpP.x >> tmpP.y;
        p.push_back(tmpP);
    }
    solve();
}