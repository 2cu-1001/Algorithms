#include <bits/stdc++.h>
using namespace std;
int T, N, M, ans, posCnt, arr[100][100], ch[10010], assign[10010];
int dx[4] = { -1, -1, 0, 0 };
int dy[4] = { -1, 1, 1, -1 };
vector<int> adj[10010];
void makeGraph()
{
    for(int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++) {
            if (!arr[i][j]) continue;
            int cur = (i - 1) * M + j, nxt;
            for (int k = 0; k < 4; k++) {
                int nx = i + dx[k], ny = j + dy[k];
                if (nx < 1 || nx > N || ny < 1 || ny > M || !arr[nx][ny]) continue;
                nxt = (nx - 1) * M + ny;
                adj[cur].push_back(nxt);
                if (k < 2) adj[nxt].push_back(cur);
            }
        }
}
int DFS(int cur)
{
    for (auto nxt : adj[cur]) {
        if (ch[nxt]) continue;
        ch[nxt] = 1;
        if (!assign[nxt] || DFS(assign[nxt])) {
            assign[nxt] = cur; return 1;
        }
    }
    return 0;
}
void solve()
{
    makeGraph();
    vector<int> src;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j += 2) {
            if (!arr[i][j]) continue;
            src.push_back((i - 1) * M + j);
        }
    for (int i : src) {
        fill(ch, ch + N * M + 1, 0);
        if (DFS(i)) ans++;
        if (ans > N * M) break;
    }
    cout << posCnt - ans << "\n";
}
void init()
{
    posCnt = ans = 0;
    for (int i = 0; i < 10010; i++) adj[i].clear();
    memset(ch, 0, sizeof(ch));
    memset(assign, 0, sizeof(assign));
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> N >> M;
        for (int i = 1; i <= N; i++) {
            string s; cin >> s;
            for (int j = 1; j <= M; j++) {
                arr[i][j] = s[j - 1];
                arr[i][j] = (arr[i][j] == '.' ? 1 : 0);
                if (arr[i][j]) posCnt++;
            }
        }
        solve();
        init();
    }   
}