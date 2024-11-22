#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
int V, E, ans, src, snk, cap[2010][2010], flow[2010][2010], cost[2010][2010],
	isInQueue[2010], dist[2010], pre[2010];
vector<int> adj[2010];
queue<int> q;
// inputNode : 1 ~ 1000, outputNode : 1001 ~ 2000
void SPFA()
{
	q.push(src);
	dist[src] = 0; isInQueue[src] = 1;
	while (!q.empty()) {
		int cur = q.front(); q.pop();
		isInQueue[cur] = 0;
		for (int nxt : adj[cur]) {
			if (dist[nxt] > dist[cur] + cost[cur][nxt] && cap[cur][nxt] > flow[cur][nxt]) {
				dist[nxt] = dist[cur] + cost[cur][nxt];
				pre[nxt] = cur;
				if (isInQueue[nxt]) continue;
				q.push(nxt); isInQueue[nxt] = 1;
			}
		}
	}
}
void makeGraph()
{
	for (int i = 1; i <= V; i++) {
		cost[i][i + 1000] = 0;
		cap[i][i + 1000] = 1;
		adj[i].push_back(i + 1000);
	}
	cap[src][src + 1000] = 2; cap[snk][snk + 1000] = 2;
}
void solve()
{
	src = 1; snk = V;
	makeGraph();
	while (1) {
		fill(&dist[0], &dist[2009], INT_MAX / 2);
		fill(&pre[0], &pre[2009], -1);
		fill(&isInQueue[0], &isInQueue[2009], 0);

		SPFA();
		if (pre[snk + 1000] == -1) break;

		int curMinFlow = INT_MAX;
		for (int i = pre[snk + 1000]; i != src; i = pre[i]) {
			int nxtNode = pre[i];
			curMinFlow = min(curMinFlow, cap[nxtNode][i] - flow[nxtNode][i]);
			cost[i + 1000][nxtNode - 1000] = -1 * cost[nxtNode][i];
		}

		for (int i = pre[snk + 1000]; i != src; i = pre[i]) {
			int nxtNode = pre[i];
			ans += cost[nxtNode][i];
			flow[nxtNode][i] += curMinFlow;
			flow[i][nxtNode] -= curMinFlow;
		}
	}
	cout << ans << "\n";
}
void init()
{
	ans = 0;
	fill(&cap[0][0], &cap[2009][2009], 0);
	fill(&flow[0][0], &flow[2009][2009], 0);
	fill(&cost[0][0], &cost[2009][2009], INT_MAX / 3);
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	while (cin >> V >> E) {
		init();
		for (int i = 1; i <= E; i++) {
			int u, v, c, uIn, uOut, vIn, vOut; cin >> u >> v >> c;
			uIn = u; uOut = u + 1000; vIn = v; vOut = v + 1000;
			adj[uOut].push_back(vIn); adj[vIn].push_back(uOut);
			cost[uOut][vIn] = c; cost[vIn][uOut] = -1 * c; cap[uOut][vIn] = 1;
		}
		solve();
	}
}