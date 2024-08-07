#include <bits/stdc++.h>
#define x first
#define y second
#define ll long long
using namespace std;
ll bn, wn, T;
vector<pair<ll, ll>> bp, wp;
vector<ll> bst, wst;
ll ccw(ll x1, ll x2, ll x3, ll y1, ll y2, ll y3)
{
    ll result;
    result = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
    if (result > 0) return 1;
    else if (result < 0) return -1;
    else return 0;
}
ll dist(ll x1, ll x2, ll y1, ll y2)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}
bool cmp(pair<ll, ll> a, pair<ll, ll> b)
{
    if (a.y == b.y) return a.x < b.x;
    return a.y < b.y;
}
bool cmpb(pair<ll, ll> a, pair<ll, ll> b)
{
    ll c = ccw(bp[0].x, a.x, b.x, bp[0].y, a.y, b.y);
    if (c == 0)
        return dist(bp[0].x, a.x, bp[0].y, a.y) < dist(bp[0].x, b.x, bp[0].y, b.y);
    return c > 0;
}
bool cmpw(pair<ll, ll> a, pair<ll, ll> b)
{
    ll c = ccw(wp[0].x, a.x, b.x, wp[0].y, a.y, b.y);
    if (c == 0)
        return dist(wp[0].x, a.x, wp[0].y, a.y) < dist(wp[0].x, b.x, wp[0].y, b.y);
    return c > 0;
}
void convexhull()
{
    sort(bp.begin(), bp.end(), cmp);
    sort(bp.begin() + 1, bp.end(), cmpb);
    for (int i = 0; i < bn; i++)
    {
        while (bst.size() >= 2 && ccw(bp[bst[bst.size() - 2]].x, bp[bst[bst.size() - 1]].x, bp[i].x,
            bp[bst[bst.size() - 2]].y, bp[bst[bst.size() - 1]].y, bp[i].y) <= 0) bst.pop_back();
        bst.push_back(i);
    }
    sort(wp.begin(), wp.end(), cmp);
    sort(wp.begin() + 1, wp.end(), cmpw);
    for (int i = 0; i < wn; i++)
    {
        while (wst.size() >= 2 && ccw(wp[wst[wst.size() - 2]].x, wp[wst[wst.size() - 1]].x, wp[i].x,
            wp[wst[wst.size() - 2]].y, wp[wst[wst.size() - 1]].y, wp[i].y) <= 0) wst.pop_back();
        wst.push_back(i);
    }
}
bool is_b_inside_w()
{
    for (int w = 0; w < wst.size(); w++)
    {
        ll p1 = wst[w], p2 = wst[(w + 1) % wst.size()];
        for (int b = 0; b < bn; b++)
        {
            ll ccw_ = ccw(wp[p1].x, wp[p2].x, bp[b].x, wp[p1].y, wp[p2].y, bp[b].y);
            if (ccw_ <= 0) return false;
        }
    }
    return true;
}
bool is_w_inside_b()
{
    for (int b = 0; b < bst.size(); b++)
    {
        ll p1 = bst[b], p2 = bst[(b + 1) % bst.size()];
        for (int w = 0; w < wn; w++)
        {
            ll ccw_ = ccw(bp[p1].x, bp[p2].x, wp[w].x, bp[p1].y, bp[p2].y, wp[b].y);
            if (ccw_ <= 0) return false;
        }
    }
    return true;
}
ll is_intersect(pair<pair<ll, ll>, pair<ll, ll>> l1, pair<pair<ll, ll>, pair<ll, ll>> l2)
{
    pair<ll, ll> l1p1 = l1.x, l1p2 = l1.y, l2p1 = l2.x, l2p2 = l2.y;
    ll ccw1 = ccw(l1p1.x, l1p2.x, l2p1.x, l1p1.y, l1p2.y, l2p1.y) *
        ccw(l1p1.x, l1p2.x, l2p2.x, l1p1.y, l1p2.y, l2p2.y);
    ll ccw2 = ccw(l2p1.x, l2p2.x, l1p1.x, l2p1.y, l2p2.y, l1p1.y) *
        ccw(l2p1.x, l2p2.x, l1p2.x, l2p1.y, l2p2.y, l1p2.y);
    if (ccw1 == 0 && ccw2 == 0)
    {
        if (l1p1 > l1p2) swap(l1p1, l1p2);
        if (l2p1 > l2p2) swap(l2p1, l2p2);
        return l2p1 <= l1p2 && l1p1 <= l2p2;
    }
    return ccw1 <= 0 && ccw2 <= 0;
}
void solve()
{
    bool result;
    convexhull();
    result = is_b_inside_w();
    if (result)
    {
        cout << "NO\n";
        return;
    }
    result = is_w_inside_b();
    if (result)
    {
        cout << "NO\n";
        return;
    }
    for (int b = 0; b < bst.size(); b++) //b변, w잠
    {
        ll l1p1 = bst[b], l1p2 = bst[(b + 1) % bst.size()];
        for (int w = 0; w < wst.size(); w++)
        {
            ll l2p1 = wst[w], l2p2 = wst[(w + 1) % wst.size()];
            result = is_intersect({ bp[l1p1], bp[l1p2] }, { wp[l2p1], wp[l2p2] });
            if (result)
            {
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    while (T--)
    {
        bp.clear(); wp.clear();
        bst.clear(); wst.clear();
        cin >> bn >> wn;
        for (int i = 1; i <= bn; i++)
        {
            ll a, b; cin >> a >> b;
            bp.push_back({ a, b });
        }
        for (int i = 1; i <= wn; i++)
        {
            ll a, b; cin >> a >> b;
            wp.push_back({ a, b });
        }
        solve();
    }
}