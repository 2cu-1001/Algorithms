#include <bits/stdc++.h>
using namespace std;
int N, arr[20][20], d[20][10][1<<15];
int DFS(int cur, int vis, int pre_val)
{
	if (d[cur][pre_val][vis] != -1) return d[cur][pre_val][vis];
	if (vis == (1 << N) - 1) return 1;
	d[cur][pre_val][vis] = 1;
	for (int i = 0; i < N; i++)
	{
		if (i == cur) continue;
		if (pre_val > arr[cur][i] || (vis & (1 << i)) != 0) continue;
		d[cur][pre_val][vis] = max(d[cur][pre_val][vis], DFS(i, (vis | (1 << i)), arr[cur][i]) + 1);
	}
	return d[cur][pre_val][vis];
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		string s; cin >> s;
		for (int j = 0; j < N; j++) arr[i][j] = s[j] - '0';
	}
	memset(d, -1, sizeof(d));
	cout << DFS(0, 1, 0);
}