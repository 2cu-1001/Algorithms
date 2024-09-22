#include<iostream>
#include<math.h>
#include<vector>
#include<algorithm>
using namespace std;
#define p pair<int, int>
#define f first
#define s second
 
int n, m, b, c, base, seg[1 << 17], x, y, smax, ret;
vector<p> v;
bool xchk, ychk;
 
int search(int idx, int l, int r,int xx,int yy) {
    if (xx > r || yy < l)return 0;
    if (xx <= l && yy >= r)return seg[idx];
    int mid = (l + r + 1) / 2;
    return max(search(idx * 2, l, mid - 1, xx, yy), search(idx * 2 + 1, mid, r, xx, yy));
}
 
int solve() {
    y = lower_bound(v.begin(), v.end(), make_pair(b, 0)) - v.begin();
    x = lower_bound(v.begin(), v.end(), make_pair(c, 0)) - v.begin();
    xchk = x < n&&v[x].f == c;
    ychk = y < n&&v[y].f == b;
    if (xchk&&ychk&&v[x].s > v[y].s)return -1;//false
    smax = search(1, 1, base, lower_bound(v.begin(), v.end(), make_pair(b + 1, 0)) - v.begin() + 1, x);
    if (xchk&&smax >= v[x].s)return -1;
    if (ychk&&smax >= v[y].s)return -1;
    if (xchk && ychk&&x - y == c - b)return 0;//true
    return 1;//maybe
}
 
int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    base = pow(2, (int)log2(n) + 1);
    for (int i = base; i < base + n; i++) {
        cin >> x >> y;
        v.push_back({ x,y });
        seg[i] = y;
    }
    for (int i = base - 1; i > 0; i--)seg[i] = max(seg[i * 2], seg[i * 2 + 1]);
    cin >> m;
    while (m--) {
        cin >> b >> c;
        ret = solve();
        if (ret > 0)cout << "maybe\n";
        else if (!ret)cout << "true\n";
        else cout << "false\n";
    }
}
