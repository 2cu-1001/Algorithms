//2423
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
int dxa[4] = { 0, 0, 1, 1 }, dya[4] = { 0, 1, 1, 0 };
int dx[4] = { -1, -1, 1, 1 }, dy[4] = { -1, 1, 1, -1 };
int N, M, arr[510][510], cnt[510][510];
void solve()
{
    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= M; j++) cnt[i][j] = 1000000;
    priority_queue<pair<int, pair<int, int>>, 
        vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    pq.push({ 0, {0, 0} }); cnt[0][0] = 0;
    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        if (cur.x != cnt[cur.y.x][cur.y.y]) continue; {
            for (int k = 0; k < 4; k++) {
                int nxa = cur.y.x + dxa[k], nya = cur.y.y + dya[k], 
                    nx = cur.y.x + dx[k], ny = cur.y.y + dy[k];
                if (nxa < 1 || nya < 1 || nxa > N || nya > M) continue;
                if (k % 2 == 0) {
                    if (arr[nxa][nya] == '\\') {
                        if (cnt[nx][ny] > cur.x) {
                            cnt[nx][ny] = cur.x; pq.push({ cur.x, {nx, ny} });
                        }
                    }
                    else {
                        if (cnt[nx][ny] > cur.x + 1) {
                            cnt[nx][ny] = cur.x + 1; pq.push({ cur.x + 1, {nx, ny} });
                        }
                    }
                        
                }
                else if (k % 2 == 1) {
                    if (arr[nxa][nya] == '/') {
                        if (cnt[nx][ny] > cur.x) {
                            cnt[nx][ny] = cur.x; pq.push({ cur.x, {nx, ny} });
                        }
                    }
                    else {
                        if (cnt[nx][ny] > cur.x + 1) {
                            cnt[nx][ny] = cur.x + 1; pq.push({ cur.x + 1, {nx, ny} });
                        }
                    }
                }
            }
        }
    }
    if (cnt[N][M] != 1000000) cout << cnt[N][M];
    else cout << "NO SOLUTION";
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        string s; cin >> s;
        for (int j = 1; j <= M; j++) arr[i][j] = s[j - 1];
    }
    solve();
    return 0;
}