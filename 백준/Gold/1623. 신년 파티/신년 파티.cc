#include <bits/stdc++.h>
using namespace std;
int n, arr[200010], d[2][200010], ch[200010];
//d[0][i] : i번이 안갈 때 i번과 i번 서브트리까지 최대값
//d[1][i] : i번이 갈 때 i번과 i번 서브트리까지 최대값
vector<int> adj[200010], ans;
void DFS(int x)
{
	int t0 = 0, t1 = 0;
	//t0 : x의 자식 다 안가는 경우 합
	//t1 : x의 자식 중 가는 경우가 있을 경우 최대값
	if (adj[x].empty())
	{
		d[0][x] = 0;
		d[1][x] = arr[x];
		return;
	}
	for (int nxt : adj[x])
	{
		DFS(nxt);
		t0 += d[0][nxt];
		t1 += max(d[0][nxt], d[1][nxt]);
	}
	if (t0 >= t1)
	{
		d[0][x] = t0;
		d[1][x] = t0 + arr[x];
	}
	else if (t0 < t1)
	{
		d[0][x] = t1;
		d[1][x] = t0 + arr[x];
	}
	return;
}
void get_path(int cur, int is_cur_go)
{
	if (is_cur_go) ans.push_back(cur);
	for (int nxt : adj[cur])
	{
		if (is_cur_go) get_path(nxt, 0);
		else if (!is_cur_go)
		{
			if (d[0][nxt] >= d[1][nxt])
			{
				get_path(nxt, 0);
			}
			else if(d[0][nxt] < d[1][nxt])
			{
				get_path(nxt, 1);
			}
		}
	}
}
void solve()
{
	DFS(1);
	cout << d[1][1] << " " << d[0][1] << "\n";
	get_path(1, 1);
	sort(ans.begin(), ans.end());
	for (int nxt : ans) cout << nxt << " ";
	cout << -1 << "\n";
	ans.clear();
	get_path(1, 0);
	sort(ans.begin(), ans.end());
	for (int nxt : ans) cout << nxt << " ";
	cout << -1 << "\n";
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> arr[i];
	for (int i = 2; i <= n; i++)
	{
		int parent; cin >> parent;
		if (parent == i) continue;
		adj[parent].push_back(i);
	}
	solve();
}