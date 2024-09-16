#include <bits/stdc++.h>
using namespace std;
int N, M, ch[2010], sccNum[2010];
vector<int> adj[2010], radj[2010];
vector<vector<int>> ans;
stack<int> st;
void init()
{
    for (int i = 1; i <= 2005; i++) {
        adj[i].clear(); radj[i].clear(); sccNum[i] = 0; ch[i] = 0;
    }
    while (!st.empty()) st.pop();
}
void DFS(int n)
{
    ch[n] = 1;
    for (int nxt : adj[n]) {
        if (ch[nxt] == 1) continue;
        DFS(nxt);
    }
    st.push(n);
    return;
}
void RDFS(int n, vector<int>(&tmp), int sccCnt)
{
    ch[n] = 1;
    for (int nxt : radj[n]) {
        if (ch[nxt] == 1) continue;
        tmp.push_back(nxt);
        sccNum[nxt] = sccCnt;
        RDFS(nxt, tmp, sccCnt);
    }
    return;
}
void kosaraju()
{
    for (int i = 1; i <= 2 * N; i++) {
        if (ch[i] == 1) continue;
        DFS(i);
    }
    memset(ch, 0, sizeof(ch));
    int sccCnt = 1;
    while (!st.empty()) {
        int cur = st.top();
        st.pop();
        if (ch[cur] == 1) continue;
        vector<int> tmp;
        tmp.push_back(cur);
        sccNum[cur] = sccCnt;
        RDFS(cur, tmp, sccCnt);
        sort(tmp.begin(), tmp.end());
        ans.push_back(tmp);
        sccCnt++;
    }
}
void solve()
{
    kosaraju();
    for(int i = 1; i <= N; i++) 
        if (sccNum[i] == sccNum[i + N]) {
            cout << "no\n"; return;
        }
    cout << "yes\n";
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	while (cin >> N >> M) {
		for (int i = 1; i <= M; i++) {
			int u, v; cin >> u >> v;
            if (u < 0) u = -u + N;
            if (v < 0) v = -v + N;

            if (u <= N) {
                adj[N + u].push_back(v);
                radj[v].push_back(N + u);
            }
            else {
                adj[u - N].push_back(v);
                radj[v].push_back(u - N);
            }

            if (v <= N) {
                adj[N + v].push_back(u);
                radj[u].push_back(N + v);
            }
            else {
                adj[v - N].push_back(u);
                radj[u].push_back(v - N);
            }
		}
        adj[N + 1].push_back(1);
        radj[1].push_back(N + 1);
        solve();
        init();
	}
}