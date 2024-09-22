#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n, q;
ll arr[100010], tree[400010];
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
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    init(1, 1, n);
    for (int j = 0; j < q; j++)
    {
        ll x, y, a, b;
        cin >> x >> y >> a >> b;
        if (x > y) swap(x, y);
        cout << sum(1, 1, n, x, y) << "\n";
        ll diff = b - arr[a];
        arr[a] = b;
        update(1, 1, n, a, diff);
    }
}