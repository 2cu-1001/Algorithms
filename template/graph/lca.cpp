int LCA(int x, int y)
{
    //dp(), dfs() 먼저 호출하고 호출할 것
    if (depth[x] < depth[y]) swap(x, y); // x가 더 깊은 노드
    for (int i = h; i >= 0; i--)
        if (depth[x] - depth[y] >= (1 << i))
            x = parent[x][i];
    if (x == y) return x;
    for (int i = h; i >= 0; i--)
    {
        if (parent[x][i] == parent[y][i]) continue;
        x = parent[x][i];
        y = parent[y][i];
    }
    return parent[x][0];
}
void DP()
{
    for(int j = 1; j<=h; j++)
        for (int i = 1; i <= n; i++)
            parent[i][j] = parent[parent[i][j - 1]][j - 1];
}
void DFS(int cur, int dep, int par)
{
    depth[cur] = dep;
    for (int nxt : adj[cur])
    {
        if (ch[nxt] || nxt == par) continue;
        parent[nxt][0] = cur;
        ch[nxt] = 1;
        DFS(nxt, dep + 1, cur);
    }
}
