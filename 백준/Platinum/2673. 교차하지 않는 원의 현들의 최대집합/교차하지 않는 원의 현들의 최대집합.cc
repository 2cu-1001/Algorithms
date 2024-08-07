#include <bits/stdc++.h>
using namespace std;
int N, adj[110][110], d[110][110];
void solve()
{
	for (int i = 1; i <= 100; i++)
		for (int j = i; j >= 1; j--)
			for (int k = j; k < i; k++)
				d[j][i] = max(d[j][i], d[j][k] + d[k][i] + adj[i][j]);
	cout << d[1][100];
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int u, v;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> u >> v;
		adj[u][v] = adj[v][u] = 1;
	}
	solve();
	return 0;
}