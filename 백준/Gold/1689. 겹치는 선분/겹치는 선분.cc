#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
int N, ans, cnt, val, idx, ch[1000010];
vector<pair<int, int>> inv, v;
bool cmp(pair<int, int> p1, pair<int, int> p2)
{
	if (p1.x == p2.x) return p1.y < p2.y;
	return p1.x < p2.x;
}
void solve()
{
	sort(inv.begin(), inv.end(), cmp);
	for (int i = 0; i < N; i++) {
		v.push_back({ inv[i].x, i });
		v.push_back({ inv[i].y, i });
	}
	sort(v.begin(), v.end(), cmp);
	for (auto cur : v) {
		tie(val, idx) = cur;
		if (ch[idx]) { ans = max(ans, cnt); cnt--; }
		else { ch[idx] = 1; cnt++; }
	}
	cout << ans;
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 1; i <= N; i++) {
		int s, e; cin >> s >> e;
		inv.push_back({ s, e });
	}
	solve();
}