#include <bits/stdc++.h>
#define x first
#define y second
#define ll long long
using namespace std;
ll C, N, ch[2010];
vector<ll> ans;
vector<pair<pair<ll, ll>, ll>> poly;
bool cmp1(pair<pair<ll, ll>, ll> p1, pair<pair<ll, ll>, ll> p2)
{
    if (p1.x.x == p2.x.x) return p1.x.y < p2.x.y;
    return p1.x.x < p2.x.x;
}
ll ccw(pair<ll, ll> p1, pair<ll, ll> p2, pair<ll, ll> p3)
{
    ll result = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    if (result > 0) return 1;
    else if (result < 0) return -1;
    else return 0;
}
vector<pair<pair<ll, ll>, ll>> convexHull() {
    vector<pair<pair<ll, ll>, ll>> up;
    for (int i = 0; i < N; i++) {
        auto p = poly[i].x;
        while (up.size() >= 2 && ccw(up[(ll)up.size() - 2].x, up[(ll)up.size() - 1].x, p) > 0) {
            auto cur = up.back();
            up.pop_back(); ch[cur.y] = 0;
        }
        up.push_back(poly[i]);
        ch[poly[i].y] = 1; 
    }
    return up;
}
void solve()
{
    sort(poly.begin(), poly.end(), cmp1);

    vector<pair<pair<ll, ll>, ll>> up = convexHull();
    vector<pair<pair<ll, ll>, ll>> down;

    for (int i = 0; i < N; i++)
        if (!ch[poly[i].y]) {
            down.push_back({ poly[i].x, poly[i].y });
        }
    sort(down.begin(), down.end(), cmp1);
    reverse(down.begin(), down.end());

    for (auto i : up) cout << i.y << " ";
    for (auto i : down) cout << i.y << " ";
    if (C > 0) cout << "\n";
}
void init()
{
    poly.clear(); ans.clear();
    memset(ch, 0, sizeof(ch));
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> C;
    while (C--) {
        cin >> N;
        for (int i = 0; i < N; i++) {
            ll x_, y_; cin >> x_ >> y_;
            poly.push_back({ { x_, y_ }, i });
        }
        solve();
        init();
    }
}