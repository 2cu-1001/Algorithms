#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
int N, ans, money[200010], indegree[200010], ch[200010];
stack<int> st;
vector<pair<int, int>> adj[200010], radj[200010];
vector<int> remains;
vector<vector<int>> cycles;
void makeMoneyFlow(int cur)
{
	if (ch[cur]) return;
	ch[cur] = 1;

	ans += max(adj[cur][0].y - money[cur], 0);
	money[adj[cur][0].x] += adj[cur][0].y;
	adj[cur][0].y = 0;

	makeMoneyFlow(adj[cur][0].x);
}
void DFS(int n)
{
	ch[n] = 1;
	for (auto nxt : adj[n]) {
		if (ch[nxt.x] == 1 || indegree[nxt.x] == 0) continue;
		DFS(nxt.x);
	}
	st.push(n);
	return;
}
void RDFS(int n, vector<int>& tmp)
{
	ch[n] = 1;
	for (auto nxt : radj[n]) {
		if (ch[nxt.x] == 1 || indegree[nxt.x] == 0) continue;
		tmp.push_back(nxt.x);
		RDFS(nxt.x, tmp);
	}
	return;
}
void getCycles()
{
	for (int i : remains) {
		if (ch[i] == 1) continue;
		DFS(i);
	}
	memset(ch, 0, sizeof(ch));
	while (!st.empty()) {
		int cur = st.top();
		st.pop();
		if (ch[cur] == 1) continue;
		vector<int> tmp;
		tmp.push_back(cur);
		RDFS(cur, tmp);
		sort(tmp.begin(), tmp.end());
		cycles.push_back(tmp);
	}
}
void topologicalSort()
{
	queue<int> q;
	for (int i = 1; i <= N; i++) 
		if (indegree[i] == 0) q.push(i);
	while (!q.empty()) {
		int cur = q.front(); q.pop();
		ans += max(adj[cur][0].y - money[cur], 0);
		money[adj[cur][0].x] += adj[cur][0].y;
		indegree[adj[cur][0].x]--;
		if (indegree[adj[cur][0].x] == 0) q.push(adj[cur][0].x);
	}
	for (int i = 1; i <= N; i++) {
		if (indegree[i] != 0) remains.push_back(i);
		else if (indegree[i] == 0) ch[i] = 1;
	}
}
void solve()
{
	topologicalSort();
	getCycles();

	memset(ch, 0, sizeof(ch));
	for (auto curCycle : cycles) {
		int stNode = curCycle[0], minVal = INT_MAX;

		for (int cur : curCycle) {
			int nxt = adj[cur][0].x;
			int curVal = max(adj[nxt][0].y - money[nxt], 0);
			if (curVal < minVal) {
				minVal = curVal; stNode = nxt;
			}
		}

		makeMoneyFlow(stNode);
	}

	cout << ans;
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 1; i <= N; i++) {
		int p, c; cin >> p >> c;
		adj[i].push_back({ p, c }); radj[p].push_back({ i, c });
		indegree[p]++;
	}
	solve();
}