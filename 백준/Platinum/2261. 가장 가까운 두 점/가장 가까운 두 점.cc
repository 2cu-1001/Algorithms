#include <bits/stdc++.h>
using namespace std;
int N; 
typedef struct point {
	int x, y;
}point;
vector<point> v;
bool cmpY(point& p1, point& p2)
{
	return p1.y < p2.y;
}
bool cmp(point& p1, point& p2) 
{
	if (p1.x == p2.x) return p1.y < p2.y;
	return p1.x < p2.x;
}
int getDist(point& p1, point& p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
int mergeCpp(int d, int low, int mid, int high)
{
	int lr = INT_MAX, sz;
	vector<point> tmp;
	for (int i = low; i <= high; i++) {
		if((v[i].x - v[mid].x) * (v[i].x - v[mid].x) < d) tmp.push_back(v[i]);
	}
	sort(tmp.begin(), tmp.end(), cmpY);
	sz = (int)tmp.size();
	for(int i = 0; i < sz; i++)
		for (int j = i + 1; j < sz; j++) {
			if ((tmp[j].y - tmp[i].y) * (tmp[j].y - tmp[i].y) >= d) break;
			lr = min(lr, getDist(tmp[i], tmp[j]));
		}
	return lr;
}
int cpp(int low, int high)
{
	if (low < high - 2) {
		int mid, l, r, d, lr;
		mid = (low + high) / 2;
		l = cpp(low, mid); r = cpp(mid + 1, high);
		d = min(l, r);
		lr = mergeCpp(d, low, mid, high);
		return min(d, lr);
	}
	if (low == high - 1) return getDist(v[low], v[high]);
	return min(getDist(v[low], v[low + 1]), 
		min(getDist(v[low + 1], v[high]), getDist(v[high], v[low])));
}
void solve()
{
	sort(v.begin(), v.end(), cmp);
	cout <<  cpp(0, (int)v.size() - 1);
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	point p;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		int tx, ty; cin >> tx >> ty;
		p.x = tx; p.y = ty;
		v.push_back(p);
	}
	solve();
	return 0;
}