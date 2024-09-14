#include <bits/stdc++.h>
#define INF INT_MAX / 2
using namespace std;
int N, P, st, ed, ans, ch[810], level[810], work[810], capacity[810][810], flow[810][810];
vector<int> adj[810];
bool BFS()
{
    memset(level, -1, sizeof(level));
    level[st] = 0;
    queue<int> q; q.push(st);
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (int nxt : adj[cur]) {
            if (level[nxt] == -1 && capacity[cur][nxt] - flow[cur][nxt] > 0) {
                level[nxt] = level[cur] + 1;
                q.push(nxt);
            }
        }
    }
    return level[ed] != -1;
}
int DFS(int cur, int cur_flow)
{
    if (cur == ed) return cur_flow;
    for (int i = work[cur]; i < adj[cur].size(); i++) {
        int nxt = adj[cur][i];
        if (level[nxt] == level[cur] + 1 && capacity[cur][nxt] - flow[cur][nxt] > 0) {
            int return_val = DFS(nxt, min(capacity[cur][nxt] - flow[cur][nxt], cur_flow));
            if (return_val > 0) {
                flow[cur][nxt] += return_val;
                flow[nxt][cur] -= return_val;
                work[cur] = i;
                ch[nxt] = 1;
                return return_val;
            }
        }
    }
    work[cur] = adj[cur].size();
    return 0;
}
void Dinic()
{
    while (BFS()) {
        memset(work, 0, sizeof(work));
        while (1) {
            int cur_flow = DFS(st, INF);
            if (cur_flow == 0) break;
            ans += cur_flow;
        }
    }
}
int solve()
{
    st = 1; ed = 2;
    for (int i = 1; i <= N; i++) {
        adj[i].push_back(i + 400);
        capacity[i][i + 400] = 1;
        adj[i + 400].push_back(i);
        capacity[i + 400][i] = 0;
    }
    capacity[1][401] = capacity[2][402] = INF;
    Dinic();
    return ans;
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
    cin >> N >> P;
    int u, v;
    for (int i = 1; i <= P; i++) {
        cin >> u >> v;
        adj[u + 400].push_back(v);
        capacity[u + 400][v] = INF; //Aout Bin
        adj[v].push_back(u + 400);
        capacity[v][u + 400] = 0; //Bin Aout
        adj[v + 400].push_back(u);
        capacity[v + 400][u] = INF; //Bout Ain
        adj[u].push_back(v + 400);
        capacity[u][v + 400] = 0; //Ain Bout
    }
    cout << solve();
	return 0;
}