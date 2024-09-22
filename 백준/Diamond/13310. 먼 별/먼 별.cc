#include <bits/stdc++.h>
#define ll long long
using namespace std;
typedef struct star {
	ll ori_x, ori_y,
		dx, dy, cur_x, cur_y;
}star;
vector<star> s;
vector<int> convex_hull;
ll N, T, ans_day, ans_dist;
ll dist_calc(pair<ll, ll> p1, pair<ll, ll> p2)
{
	return (p1.first - p2.first) * (p1.first - p2.first) +
		(p1.second - p2.second) * (p1.second - p2.second);
}
ll ccw(pair<ll, ll> p1, pair<ll, ll> p2, pair<ll, ll> p3)
{
	ll result = (p2.first - p1.first) * (p3.second - p1.second) -
		(p2.second - p1.second) * (p3.first - p1.first);
	if (result > 0) return 1;
	else if (result < 0) return -1;
	else return 0;
}
ll ccw(pair<ll, ll> p1, pair<ll, ll> p2, pair<ll, ll> p3, pair<ll, ll> p4)
{
	p4.first -= (p3.first - p2.first);
	p4.second -= (p3.second - p2.second);
	return ccw(p1, p2, p4);
}
bool cmp1(star a, star b)
{
	if (a.cur_y == b.cur_y) return a.cur_x < b.cur_x;
	return a.cur_y < b.cur_y;
}
bool cmp2(star a, star b)
{
	ll c = ccw({ s[0].cur_x, s[0].cur_y }, { a.cur_x, a.cur_y }, { b.cur_x, b.cur_y });
	if (c == 0)
		return dist_calc({ s[0].cur_x, s[0].cur_y }, { a.cur_x, a.cur_y }) <
		dist_calc({ s[0].cur_x, s[0].cur_y }, { b.cur_x, b.cur_y });
	return c > 0;
}
void graham_scan()
{
	sort(s.begin(), s.end(), cmp1);
	sort(s.begin() + 1, s.end(), cmp2);
	for (int i = 0; i < N; i++)
	{
		while (convex_hull.size() >= 2 && ccw(
			{ s[convex_hull[convex_hull.size() - 2]].cur_x, s[convex_hull[convex_hull.size() - 2]].cur_y },
			{ s[convex_hull[convex_hull.size() - 1]].cur_x, s[convex_hull[convex_hull.size() - 1]].cur_y },
			{ s[i].cur_x, s[i].cur_y }) <= 0) convex_hull.pop_back();
		convex_hull.push_back(i);
	}
}
ll rotating_calipers()
{
	ll a, c = 1, sz = convex_hull.size(),
		max_dist = LLONG_MIN;
	pair<ll, ll> s1, s2;
	for (int i = 0; i < sz; i++)
	{
		a = i;
		while (c != i - 1 && ccw(
			{ s[convex_hull[a % sz]].cur_x, s[convex_hull[a % sz]].cur_y },
			{ s[convex_hull[(a + 1) % sz]].cur_x, s[convex_hull[(a + 1) % sz]].cur_y },
			{ s[convex_hull[c % sz]].cur_x, s[convex_hull[c % sz]].cur_y },
			{ s[convex_hull[(c + 1) % sz]].cur_x, s[convex_hull[(c + 1) % sz]].cur_y }) > 0)
		{
			ll tmp_dist = dist_calc({ s[convex_hull[a]].cur_x, s[convex_hull[a]].cur_y },
				{ s[convex_hull[c % sz]].cur_x, s[convex_hull[c % sz]].cur_y });
			if (tmp_dist > max_dist)
			{
				max_dist = tmp_dist;
				s1 = { s[convex_hull[a]].cur_x, s[convex_hull[a]].cur_y };
				s2 = { s[convex_hull[c % sz]].cur_x, s[convex_hull[c % sz]].cur_y };
			}
			c++;
		}
		ll tmp_dist = dist_calc({ s[convex_hull[a]].cur_x, s[convex_hull[a]].cur_y },
			{ s[convex_hull[c % sz]].cur_x, s[convex_hull[c % sz]].cur_y });
		if (tmp_dist > max_dist)
		{
			max_dist = tmp_dist;
			s1 = { s[convex_hull[a]].cur_x, s[convex_hull[a]].cur_y };
			s2 = { s[convex_hull[c % sz]].cur_x, s[convex_hull[c % sz]].cur_y };
		}
	}
	return dist_calc(s1, s2);
}
ll get_dist(ll day)
{
	for (int i = 0; i < N; i++) {
		s[i].cur_x = s[i].ori_x + day * s[i].dx;
		s[i].cur_y = s[i].ori_y + day * s[i].dy;
	}
	graham_scan();
	return rotating_calipers();
}
void solve()
{
	ll low, high, p, q, pdist, qdist;
	low = 0; high = T;
	while (high - low >= 3)
	{
		p = (low * 2 + high) / 3;
		q = (low + high * 2) / 3;
		pdist = get_dist(p);
		convex_hull.clear();
		qdist = get_dist(q);
		convex_hull.clear();
		if (pdist > qdist) low = p;
		else high = q;
	}
	ans_dist = 1e18;
	ans_day = 0;
	for (ll i = low; i <= high; i++) {
		ll tmp_dist = get_dist(i);
		convex_hull.clear();
		if (ans_dist > tmp_dist) {
			ans_dist = tmp_dist;
			ans_day = i;
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> N >> T;
	for (int i = 0; i < N; i++) {
		int x, y, dx, dy;
		cin >> x >> y >> dx >> dy;
		star tmp_star = { x, y, dx, dy, 0, 0 };
		s.push_back(tmp_star);
	}
	solve();
	cout << ans_day << "\n" << ans_dist;
}