#include <bits/stdc++.h>
using namespace std;
int n, h, r[10010], visited[10010], d[10010], par[10010], root, x, y, ans;
vector<vector<pair<int, int>>> vt;
vector<vector<int>> dph;
void dfs(int v, int dh, int dis) {
    visited[v] = true;
    d[v] = dis;
    dph[dh].push_back(v);
    if (!vt[v].size())
        r[v] = dis - h;
    for (auto next : vt[v]) {
        if (visited[next.first])
            continue;
        dfs(next.first, dh + 1, dis + next.second);
    }
}
int main() {
    cin >> n >> h;
    vt.resize(n + 1);
    dph.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x >> y;
        if (x == 0)root = i;
        else {
            par[i] = x;
            vt[x].push_back({ i,y });
        }
    }
    dfs(root, 0, 0);
    for (int i = dph.size() - 1; i >= 0; i--) 
    {
        for (auto v : dph[i]) {
            if (d[par[v]] >= r[v]) {
                r[par[v]] = max(r[v], r[par[v]]);
            }
            else {
                r[par[v]] = d[par[v]];
                ans += r[v] - d[par[v]];
            }
        }
    }
    cout << ans;
    return 0;
}
