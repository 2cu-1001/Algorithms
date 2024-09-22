#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int u_bound, ans, N, M, arr[60][60], ch[60][60];
void BFS(int r, int c)
{   
    int h, wall_h;
    wall_h = INT_MAX;
    h = arr[r][c];
    queue<pair<int, int>> q;
    vector<pair<int, int>> v;
    q.push({ r, c });
    v.push_back({ r, c });
    ch[r][c] = 1;
    while (!q.empty())
    {
        auto cur = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int nx = dx[i] + cur.x;
            int ny = dy[i] + cur.y;
            if (nx < 1 || nx > N || ny < 1 || ny > M) return;
            if (ch[nx][ny]) continue;
            if (arr[nx][ny] > h)
            {
                wall_h = min(wall_h, arr[nx][ny]);
                continue;
            }
            ch[nx][ny] = 1;
            q.push({ nx, ny });
            v.push_back({ nx, ny });
        }
    }
    for (auto nxt : v)
    {
        ans += wall_h - arr[nxt.x][nxt.y];
        arr[nxt.x][nxt.y] = wall_h;
    }
    return;
}
void solve()
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            if (arr[i][j] < u_bound)
            {
                BFS(i, j);
                for (int i_ = 1; i_ <= N; i_++)
                    for (int j_ = 1; j_ <= M; j_++)
                        ch[i_][j_] = 0;
            }
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    u_bound = -1;
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        string s; cin >> s;
        for (int j = 1; j <= M; j++)
        {
            arr[i][j] = s[j - 1] - 48;
            u_bound = max(u_bound, s[j - 1] - 48);
        }
    }
    solve();
    cout << ans;
}