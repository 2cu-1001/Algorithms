#include <bits/stdc++.h>
using namespace std;
int N, cnt, f, M, mpf[2010], isP[2010], ch[2010], asn[2010];
vector<int> v, P, ans, curAdj[2010], orgAdj[2010];
void linearSieve()
{
    memset(mpf, -1, sizeof(mpf));
    for (int i = 2; i <= 2001; i++) {
        if (mpf[i] == -1) {
            mpf[i] = i; P.push_back(i);
            isP[i] = 1;
        }
        for (int p : P) {
            int x = i * p;
            if (x > 2001) break;
            mpf[x] = p;
            if (i % p == 0) break;
        }
    }
}
void makeEdge()
{
    for (int i = 0; i < N; i++)
        for (int j = 1; j < N; j++) {
            if (i == j) continue;
            if (isP[v[i] + v[j]]) {
                orgAdj[v[i]].push_back(v[j]);
            }
        }
}
int DFS(int cur)
{
    for (int nxt : curAdj[cur]) {
        if (ch[nxt]) continue;
        ch[nxt] = 1;
        if (asn[nxt] == -1 || (asn[nxt] != f && DFS(asn[nxt]))) {
            asn[nxt] = cur; asn[cur] = nxt; return 1;
        }
    }
    return 0;
}
void solve()
{
    linearSieve();
    makeEdge();
    f = v[0];
    for (int i = 0; i <= M; i++) curAdj[i] = orgAdj[i];
    for (int k = 0; k < (int)(orgAdj[f].size()); k++) {
        curAdj[f].clear();
        curAdj[f].push_back(orgAdj[f][k]);
        memset(asn, -1, sizeof(asn));
        bool isOk = true;
        for (int cur : v) {
            memset(ch, 0, sizeof(ch));
            if (asn[cur] != -1) continue;
            if (!DFS(cur)) { isOk = false; break; }
        }
        if (isOk) ans.push_back(curAdj[f][0]);
    }
    if (ans.empty()) { cout << -1; return; }
    sort(ans.begin(), ans.end());
    for (int n : ans) cout << n << " ";
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    M = -1;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        int t; cin >> t; v.push_back(t);
        M = max(M, t);
    }
    solve();
    return 0;
}