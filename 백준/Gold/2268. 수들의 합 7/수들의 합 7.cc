#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n, m;
ll arr[1000010], tree[4000010];
int init(int node, int st, int ed)
{
	if (st == ed) return tree[node] = arr[st];
	int mid = (st + ed) / 2;
	return tree[node] = init(node * 2, st, mid) + init(node * 2 + 1, mid + 1, ed);
}
ll sum(int node, int st, int ed, int left, int right)
{
	if (left > ed || right < st) return 0;
	if (left <= st && right >= ed) return tree[node];
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
	cin >> n >> m;
	//init(1, 1, n);
	for (int i = 0; i < m; i++)
	{
		ll q, a, b;
		cin >> q >> a >> b;
		if (q == 0)
		{
			if (a > b) swap(a, b);
			cout << sum(1, 1, n, a, b) << "\n";
		}
		else if (q == 1)
		{
			ll diff = b - arr[a];
			arr[a] = b;
			update(1, 1, n, a, diff);
		}		
	}
}