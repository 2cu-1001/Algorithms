#include <bits/stdc++.h>
#define ld long double
using namespace std;
typedef struct {
    ld x, y;
}P;
int N, K;
ld learningRate = 1000, delta = 0.999;
P c, grad;
vector<P> p;
ld getDist(P p1, P p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
void getGrad()
{
    P retGrad = { 0, 0 };

    vector<pair<ld, int>> tmp;
    for (int i = 0; i < N; i++) tmp.push_back({ getDist(p[i], c), i });
    sort(tmp.begin(), tmp.end());
    reverse(tmp.begin(), tmp.end());

    for (int i = 0; i < K; i++) {
        ld curDist = tmp[i].first;
        int idx = tmp[i].second;
        if (curDist == 0) continue;
        retGrad.x += (c.x - p[idx].x) / curDist;
        retGrad.y += (c.y - p[idx].y) / curDist;
    }

    grad = retGrad;
}
ld getAns()
{
    ld ans = 0;

    vector<pair<ld, int>> tmp;
    for (int i = 0; i < N; i++) tmp.push_back({ getDist(p[i], c), i });
    sort(tmp.begin(), tmp.end());
    reverse(tmp.begin(), tmp.end());

    for (int i = 0; i < K; i++) ans += tmp[i].first;

    return ans;
}
void solve()
{
    c = { 0, 0 };
    for (auto i : p) { c.x += i.x; c.y += i.y; }
    c.x /= (ld)N; c.y /= (ld)N;

    int iterCnt = 0;
    while (iterCnt < 100000) {
        getGrad();
        c = { c.x - learningRate * grad.x, c.y - learningRate * grad.y };
        learningRate *= delta;
        iterCnt++;
    }

    cout << fixed; cout.precision(5);
    cout << getAns();
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        P tmpP; cin >> tmpP.x >> tmpP.y;
        p.push_back(tmpP);
    }
    solve();
}