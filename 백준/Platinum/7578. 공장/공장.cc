#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll N, ans, a[500010], b[500010], bp[1000010], f[500010];
int tree[2000010], arr[500010];
int query(int node, int st, int ed, int left, int right)
{
    if (left > ed || right < st) return 0;
    if (left <= st && right >= ed) return tree[node];
    int mid = (st + ed) / 2;
    return query(node * 2, st, mid, left, right) + query(node * 2 + 1, mid + 1, ed, left, right);
}
void update(int node, int st, int ed, int idx, int diff)
{
    if (st > idx || ed < idx) return;
    tree[node] += diff;
    if (st == ed) return;
    int mid = (st + ed) / 2;
    update(node * 2, st, mid, idx, diff);
    update(node * 2 + 1, mid + 1, ed, idx, diff);
}
void solve()
{
	ans = 0;
	for (int i = 1; i <= N; i++) bp[b[i]] = i;
	for (int i = 1; i <= N; i++) f[bp[a[i]]] = i;
    for (int i = 1; i <= N; i++) {
        update(1, 1, N, f[i], 1);
        ans += query(1, 1, N, f[i] + 1, N);
    }
    cout << ans;
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 1; i <= N; i++) cin >> a[i];
	for (int i = 1; i <= N; i++) cin >> b[i];
	solve();
}