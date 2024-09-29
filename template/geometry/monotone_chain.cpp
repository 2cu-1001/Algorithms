bool cmp(pair<ll, ll> p1, pair<ll, ll> p2)
{
    if (p1.x == p2.x) return p1.y < p2.y;
    return p1.x < p2.x;
}
int ccw(pair<ll, ll> p1, pair<ll, ll> p2, pair<ll, ll> p3)
{
    ll result = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    if (result > 0) return 1;
    else if (result < 0) return -1;
    else return 0;
}
vector<pair<ll, ll>> convexHull() {
    sort(poly.begin(), poly.end(), cmp); // sort by x
    if (poly.size() <= 3) return poly;
    vector<pair<ll, ll>> up, down;
    for (auto& p : poly) {
        while (up.size() >= 2 && ccw(up[(ll)up.size() - 2], up[(ll)up.size() - 1], p) >= 0)
            up.pop_back();
        up.push_back(p);
        while (down.size() >= 2 && ccw(down[(ll)down.size() - 2], down[(ll)down.size() - 1], p) <= 0)
            down.pop_back();
        down.push_back(p);
    }
    up.insert(up.end(), down.rbegin() + 1, down.rend() - 1);
    return up;
}