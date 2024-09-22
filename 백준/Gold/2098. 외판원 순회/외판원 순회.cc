#include <bits/stdc++.h>
#define INF INT_MAX / 10
using namespace std;
int N, adj[20][20], d[20][1<<16], mx;
int DFS(int cur, int visit)
{
	if (d[cur][visit] != -1) return d[cur][visit];
	if (visit == mx)
	{
		if (adj[cur][0] == 0) return INF;
		return adj[cur][0];
	}
	d[cur][visit] = INF;
	for (int i = 0; i < N; i++)
	{
		if ((visit & (1<<i)) != 0 || adj[cur][i] == 0) continue;
		d[cur][visit] = min(d[cur][visit], (DFS(i, visit | (1<<i)) + adj[cur][i]));
	}
	return d[cur][visit];
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) cin >> adj[i][j];
	memset(d, -1, sizeof(d));
	mx = (1 << N) - 1;
	cout << DFS(0, 1);
}