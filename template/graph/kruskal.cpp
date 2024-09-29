int Find(int x)
{
    if (parent[x] < 0) return x;
    return parent[x] = Find(parent[x]);
}
bool Union(int x, int y)
{
    x = Find(x);
    y = Find(y);
    if (x == y) return 0;
    if (parent[x] > parent[y]) swap(x, y);
    parent[x] += parent[y];
    parent[y] = x;
    return 1;
}
void Kruskal()
{
    int cnt = 0;
    sort(edge + 1, edge + e + 1);
    for (int i = 1; i <= e; i++) {
        int a, b, weight;
        tie(weight, a, b) = edge[i];
        if (!Union(a, b)) continue;
        cost += weight;
        cnt++;
        if (cnt == v - 1) break;
    }
}
