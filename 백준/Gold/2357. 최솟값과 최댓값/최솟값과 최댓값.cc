#include <bits/stdc++.h>
using namespace std;
int n, m;
int min_ = INT_MIN, max_ = INT_MAX;
int arr[100010], tree_max[400010], tree_min[400010];
int init_max(int node, int st, int ed)
{
	if (st == ed) return tree_max[node] = arr[st];
	int mid = (st + ed) / 2;
	return tree_max[node] = max(init_max(node * 2, st, mid), init_max(node * 2 + 1, mid + 1, ed));
}
int init_min(int node, int st, int ed)
{
	if (st == ed) return tree_min[node] = arr[st];
	int mid = (st + ed) / 2;
	return tree_min[node] = min(init_min(node * 2, st, mid), init_min(node * 2 + 1, mid + 1, ed));
}
int get_max(int node, int st, int ed, int left, int right)
{
	if (left > ed || right < st) return min_;
	if (left <= st && right >= ed) return tree_max[node];
	int mid = (st + ed) / 2;
	return max(get_max(node * 2, st, mid, left, right), get_max(node * 2 + 1, mid + 1, ed, left, right));
}
int get_min(int node, int st, int ed, int left, int right)
{
	if (left > ed || right < st) return max_;
	if (left <= st && right >= ed) return tree_min[node];
	int mid = (st + ed) / 2;
	return min(get_min(node * 2, st, mid, left, right), get_min(node * 2 + 1, mid + 1, ed, left, right));
}
void solve(int x, int y)
{
	int tmp_min, tmp_max;
	cout << get_min(1, 1, n, x, y) << "\n";
	cout << get_max(1, 1, n, x, y) << "\n";
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
	init_max(1, 1, n);
	init_min(1, 1, n);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		solve(a, b);
	}
}