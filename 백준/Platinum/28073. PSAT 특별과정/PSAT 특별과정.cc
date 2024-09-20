#include <bits/stdc++.h>
#define x first
#define y second
#define MAX 1000010
using namespace std;
int N, M, ST, ED, ansCnt, alp[110], ans[MAX], arr[MAX], ch[MAX], path[MAX];
char stc, edc;
vector<pair<int, int>> adj[MAX];
void getPath(int cur, int cnt)
{
	if (cur == ST || cnt > N) return;
	ans[cnt] = arr[cur]; ansCnt++;
	getPath(path[cur], cnt + 1);
}
void BFS()
{
	queue<int> q;
	q.push(ST); ch[ST] = 1;
	while (!q.empty()) {
		int cur = q.front(); q.pop();
		sort(adj[cur].begin(), adj[cur].end());
		for (int i = 0; i <= 105; i++) alp[i] = 0;
		for (auto nxt : adj[cur]) {
			if (!alp[nxt.x] && !path[nxt.y]) {
				alp[nxt.x] = nxt.y;
				q.push(nxt.y); ch[nxt.y] = 1; path[nxt.y] = cur;
			}
			else if (!path[nxt.y])
				for (auto nnxt : adj[nxt.y])
					if (!ch[nnxt.y]) {
						ch[nnxt.y] = 1; adj[alp[nxt.x]].push_back(nnxt);
					}
		}
	}
}
void solve()
{
	ST = N + 1; ED = N + 2;
	if (stc == edc) { cout << stc << "\n"; return; }
	for (int i = 1; i <= N; i++) {
		if (arr[i] == stc) {
			adj[i].push_back({ 100, ST });
			adj[ST].push_back({ 64, i });
		}
		else if (arr[i] == edc) {
			adj[i].push_back({ 64, ED });
			adj[ED].push_back({ 100, i });
		}
	}
	for (int i = 1; i <= N + 2; i++) sort(adj[i].begin(), adj[i].end());
	BFS();
	if (path[ED] == 0) { cout << "Aaak!\n"; return; }
	getPath(path[ED], 0);
	for (int i = ansCnt - 1; i >= 0; i--) cout << (char)ans[i];
	cout << "\n";
}
void input()
{
	cin >> N >> M >> stc >> edc;
	string s; cin >> s;
	for (int i = 1; i <= N; i++) arr[i] = s[i - 1];
	for (int i = 1; i <= M; i++) {
		int u, v; cin >> u >> v;
		adj[u].push_back({ arr[v], v }); adj[v].push_back({ arr[u], u });
	}
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	input(); solve();
	return 0;
}