#include <bits/stdc++.h>
#define x first
#define y second
#define ll long long
using namespace std;
typedef struct line {
	pair<int, int> p1, p2;
	void linePointSort()
	{
		if (p1.x == p2.x && p1.y > p2.y) swap(p1, p2);
		if (p1.y > p2.y) swap(p1, p2);
	}
}line;
int N, cnt, sz, p[3010];
line l[3010];
int Find(int a)
{
	if (p[a] < 0) return a;
	return p[a] = Find(p[a]);
}
void Union(int a, int b)
{
	a = Find(a); b = Find(b);
	if (a == b) return;
	if (p[a] > p[b]) swap(a, b);
	p[a] += p[b];
	p[b] = a;
}
int ccw(pair<int, int> p1, pair<int, int> p2, pair<int, int> p3)
{
	ll result = (p1.x * p2.y + p2.x * p3.y + p3.x * p1.y) - (p2.x * p1.y + p3.x * p2.y + p1.x * p3.y);
	if (result > 0) return 1;
	if (result < 0) return -1;
	return 0;
}
int isIntersect(line l1, line l2)
{
	pair<int, int> p1, p2, p3, p4;
	p1 = l1.p1; p2 = l1.p2; p3 = l2.p1; p4 = l2.p2;
	int p1p2 = ccw(p1, p2, p3) * ccw(p1, p2, p4), p3p4 = ccw(p3, p4, p1) * ccw(p3, p4, p2);
	
	if (p1p2 == 0 && p3p4 == 0) {
		if (p1 > p2) swap(p2, p1);
		if (p3 > p4) swap(p3, p4);
		return p3 <= p2 && p1 <= p4;
	}
	return p1p2 <= 0 && p3p4 <= 0;
}
void solve()
{
	sz = 1;
	for (int i = 1; i <= N; i++) {
		p[i] = -1; 
		l[i].linePointSort();
	}

	for (int i = 1; i <= N; i++)
		for (int j = i + 1; j <= N; j++) 
			if (isIntersect(l[i], l[j])) Union(i, j);
	
	for (int i = 1; i <= N; i++) Find(i);

	for (int i = 1; i <= N; i++) {
		sz = min(sz, p[i]);
		if (p[i] < 0) cnt++;
	}
	cout << cnt << "\n" << -1 * sz;
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> l[i].p1.x >> l[i].p1.y >> l[i].p2.x >> l[i].p2.y;
	}
	solve();
}