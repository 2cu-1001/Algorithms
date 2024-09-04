#include <bits/stdc++.h>
#define MAX 2001
using namespace std;
int T, A, B, isP[2010], mpf[2010];
vector<int> P;
void linearSieve()
{
    memset(mpf, -1, sizeof(mpf));
    for (int i = 2; i <= MAX; i++) {
        if (mpf[i] == -1) {
            mpf[i] = i; isP[i] = 1;
            P.push_back(i); 
        }
        for (int p : P) {
            int x = p * i;
            if (x > MAX) break;
            mpf[x] = p;
            if (i % p == 0) break;
        }
    }
}
string solve()
{
    int sw = 1, k = 0, s = 0, cur = 0;
    while (cur < B) {
        int nxt = -1, cnt = 0;
        for (int i = cur + 1; i <= min(cur + A, B); i++) 
            if (isP[i]) { nxt = i; cnt++; }
        if (sw == 1) k += cnt;
        else s += cnt;
        cur = nxt == -1 ? cur + 1 : nxt;
        sw *= -1;
        if (cur >= B) break;
    }
    if (k > s) return "kuro";
    else if (k < s) return "siro";
    else return "draw";
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    linearSieve();
    cin >> T;
    while (T--) {
        cin >> A >> B;
        cout << solve() << "\n";
    }
    return 0;
}