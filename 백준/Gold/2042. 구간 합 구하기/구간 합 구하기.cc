#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n, m, k;
ll arr[1000010];
ll tree[4000010];
ll init(int node, int st, int ed)
{
	if (st == ed) return tree[node] = arr[st];
	int mid = (st + ed) / 2;
	return tree[node] = init(node * 2, st, mid) + init(node * 2 + 1, mid + 1, ed);
}
ll sum(int node, int st, int ed, int left, int right)
{
	if (left > ed || right < st)
		return 0;
	if (left <= st && right >= ed)
		return tree[node];
	int mid = (st + ed) / 2;
	return sum(node * 2, st, mid, left, right) + sum(node * 2 + 1, mid + 1, ed, left, right);
}
void update(int node, int st, int ed, int idx, ll diff)
{
	if (st > idx || ed < idx) return;
	tree[node] += diff;
	if (st == ed) return;
	int mid = (st + ed) / 2;
	update(node * 2, st, mid, idx, diff);
	update(node * 2 + 1, mid + 1, ed, idx, diff);
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
	{
		ll t; cin >> t; 
		arr[i] = t;
	}
	init(1, 1, n);
	for (int i = 0; i < m + k; i++)
	{
		int q; cin >> q;
		if (q == 1)
		{
			ll idx, tmp;
			cin >> idx >> tmp;
			ll diff = tmp - arr[idx];
			arr[idx] = tmp;
			update(1, 1, n, idx, diff);
		}
		else if (q == 2)
		{
			ll left, right;
			cin >> left >> right;
			cout << sum(1, 1, n, left, right) << "\n";
		}
	}
}