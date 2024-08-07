#include <bits/stdc++.h>
#define x first
#define y second
#define INF INT_MAX
using namespace std;
struct edge {
	int v, cap, idx;
	edge(int v, int cap, int idx) :v(v), cap(cap), idx(idx) {}
};
int N, M, stN, edN, ans, arr[110][110], dist[110][110], level[20010], work[20010];
int dx[4] = { -1, 0, 1, 0 }; 
int dy[] = { 0, -1, 0, 1 };
pair<int, int> st, ed;
vector<edge> adj[20010];
bool BFS()
{
	memset(level, -1, sizeof(level));
	queue<int> q; level[stN] = 0; q.push(stN);
	while (!q.empty()) {
		int cur = q.front(); q.pop();
		for (edge nxt : adj[cur]) {
			if (level[nxt.v] == -1 && nxt.cap > 0) {
				level[nxt.v] = level[cur] + 1;
				q.push(nxt.v);
			}
		}
	}
	return level[edN] != -1;
}
int DFS(int cur, int curFlow)
{
	if (cur == edN) return curFlow;
	for (int& i = work[cur]; i < adj[cur].size(); i++) {
		int nxt = adj[cur][i].v, cap = adj[cur][i].cap;
		if (level[nxt] == level[cur] + 1 && cap > 0) {
			int retVal = DFS(nxt, min(cap, curFlow));
			if (retVal > 0) {
				adj[cur][i].cap -= retVal;
				adj[nxt][adj[cur][i].idx].cap += retVal;
				return retVal;
			}
		}
	}
	return 0;
}
void Dinic()
{
	while (BFS()) {
		memset(work, 0, sizeof(work));
		while (1) {
			int curFlow = DFS(stN, INF);
			if (curFlow == 0) break;
			ans += curFlow;
		}
	}
}
void init()
{
	queue<pair<int, int>> q;
	dist[st.x][st.y] = 1;
	q.push({ st.x, st.y });
	while (!q.empty()) {
		auto cur = q.front(); q.pop();
		for (int k = 0; k < 4; k++) {
			int nx = cur.x + dx[k], ny = cur.y + dy[k];
			if (nx < 1 || nx > N || ny < 1 || ny > M || 
				arr[nx][ny] == '#' || dist[nx][ny] != 0) continue;
			dist[nx][ny] = dist[cur.x][cur.y] + 1;
			q.push({ nx, ny });
		}
	}
    for(int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++) {
			int inN = (i - 1) * M + j, outN = inN + 10000;
			if (!(inN == stN || inN == edN)) {
				adj[inN].emplace_back(edge(outN, 1, (int)adj[outN].size()));
				adj[outN].emplace_back(edge(inN, 0, (int)adj[inN].size() - 1));
				for (int k = 0; k < 4; k++) {
					int nx = i + dx[k], ny = j + dy[k];
					if (nx < 1 || nx > N || ny < 1 || ny > M || arr[nx][ny] == '#') continue;
					int nxtN = (nx - 1) * M + ny;
					adj[outN].emplace_back(edge(nxtN, INF, (int)adj[nxtN].size()));
					adj[nxtN].emplace_back(edge(outN, 0, (int)adj[outN].size() - 1));
				}
			}
			else {
				for (int k = 0; k < 4; k++) {
					int nx = i + dx[k], ny = j + dy[k];
					if (nx < 1 || nx > N || ny < 1 || ny > M || arr[nx][ny] == '#') continue;
					int nxtN = (nx - 1) * M + ny;
					adj[inN].emplace_back(edge(nxtN, INF, (int)adj[nxtN].size()));
					adj[nxtN].emplace_back(edge(inN, 0, (int)adj[inN].size() - 1));
				}
			}
		}
}
void solve()
{
	stN = (st.x - 1) * M + st.y; edN = (ed.x - 1) * M + ed.y;
    init();
	if (dist[ed.x][ed.y] == 0) { cout << 0; return; }
	if (dist[ed.x][ed.y] == 2) { cout << -1; return; }
    Dinic();
    cout << ans;
}
void input()
{
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		string s; cin >> s;
		for (int j = 1; j <= M; j++) {
            arr[i][j] = s[j - 1];
			if (arr[i][j] == 'K') st = { i, j };
			else if (arr[i][j] == 'H') ed = { i, j };
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	input();
	solve();
	return 0;
}