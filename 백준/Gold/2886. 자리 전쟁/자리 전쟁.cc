#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
int N, M, ans, arr[110][110], ch[10010], sch[10010];
vector<pair<int, int>> person, seat; // dist, seat, person
vector<pair<int, pair<int, int>>> v;
bool cmp(pair<int, pair<int,int>> p1, pair<int, pair<int,int>> p2) {
    if (p1.x == p2.x) return p1.y.x < p2.y.x;
    return p1.x < p2.x;
}
int get_dist(pair<int, int> p1, pair<int, int> p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) 
        + (p1.y - p2.y) * (p1.y - p2.y);
}
void solve()
{
    int ssz, psz, predist, preseat, isCombat;
    ssz = seat.size(); psz = person.size();
    for (int i = 0; i < ssz; i++)
        for (int j = 0; j < psz; j++) v.push_back({ get_dist(seat[i], person[j]), {i, j} });
    for (int i = 0; i < psz + 2; i++) ch[i] = -1;
    sort(v.begin(), v.end(), cmp);
    predist = -1; preseat = -1; isCombat = 0;
     for (auto c : v) {
        if (predist == c.x && preseat == c.y.x) {
            if (!isCombat) {
                if (ch[c.y.y] == -1) {
                    ch[c.y.y] = c.y.x; isCombat = 1; ans++;
                }
            }
            else if (isCombat) {
                if (ch[c.y.y] == -1) ch[c.y.y] = c.y.x;
            }
        }
        else {           
            if (sch[c.y.x] == 0) {
                if (ch[c.y.y] == -1) {
                    ch[c.y.y] = c.y.x; sch[c.y.x] = 1;
                    predist = c.x; preseat = c.y.x; isCombat = 0;
                }
            }
            
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        string s; cin >> s;
        for (int j = 1; j <= M; j++) {
            arr[i][j] = s[j - 1];
            if (arr[i][j] == 'X') person.push_back({ i, j });
            else if (arr[i][j] == 'L') seat.push_back({ i, j });
        }
    } 
    solve();
    cout << ans;
    return 0;
}