int st, ed, level[sz], work[sz], flow[sz][sz], capacity[sz][sz];
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
                return return_val;
            }
        }
    }
    work[cur] = adj[cur].size();
    return 0;
}
int Dinic()
{
    int ret;
    while (BFS()) {
        memset(work, 0, sizeof(work));
        while (1) {
            int cur_flow = DFS(st, INF);
            if (cur_flow == 0) break;
            ret += cur_flow;
        }
    }
    return ret;
}
