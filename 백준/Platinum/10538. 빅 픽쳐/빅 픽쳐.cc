#include <bits/stdc++.h>
#define ll long long
#define p (long long int)1e+9
#define a1 (long long int)37
#define a2 (long long int)5831
using namespace std;
ll ans, ptW, ptH, scW, scH, ptHash, ppow1[2020], ppow2[2020], 
    ptArr[2010][2010], scArr[2010][2010], scHashArr[2010][2010];
void getPow1()
{
    ppow1[0] = 1;
    for (int i = 1; i <= max(scW, scH) + 10; i++)
        ppow1[i] = (ppow1[i - 1] * a1) % p;
}
void getPow2()
{
    ppow2[0] = 1;
    for (int i = 1; i <= max(scW, scH) + 10; i++)
        ppow2[i] = (ppow2[i - 1] * a2) % p;
}
void rabinKarp()
{
    for (int i = 0; i < ptH; i++) {
        ll tmpHash = 0;
        for (int j = 0; j < ptW; j++)
            tmpHash = (tmpHash + (ptArr[i][j] * ppow1[ptW - j - 1]) % p) % p;
        ptHash = (ptHash + (tmpHash * ppow2[ptH - i - 1]) % p) % p;
    }

    for (int i = 0; i < scH; i++) {
        ll tmpHash = 0;

        for (int j = 0; j < scW - ptW + 1; j++) {
            if (j == 0)
                for (int k = 0; k < ptW; k++)
                    tmpHash = (tmpHash + (scArr[i][k] * ppow1[ptW - k - 1]) % p ) % p;
            else {
                tmpHash = (tmpHash - scArr[i][j - 1] * ppow1[ptW - 1]) % p;
                if (tmpHash < 0) tmpHash += p;
                tmpHash = ((tmpHash * a1) % p + scArr[i][j + ptW - 1]) % p;
            }
            scHashArr[i][j] = tmpHash;
        }
    }

    for (int j = 0; j < scW - ptW + 1; j++) {
        ll scHash = 0;

        for (int i = 0; i < scH - ptH + 1; i++) {
            if (i == 0)
                for (int k = 0; k < ptH; k++)
                    scHash = (scHash + (scHashArr[k][j] * ppow2[ptH - k - 1]) % p) % p;
            else {
                scHash = (scHash - scHashArr[i - 1][j] * ppow2[ptH - 1]) % p;
                if (scHash < 0) scHash += p;
                scHash = ((scHash * a2) % p + scHashArr[i + ptH - 1][j]) % p;
            }
            if (scHash == ptHash) ans++;
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> ptH >> ptW >> scH >> scW;
    for (int i = 0; i < ptH; i++) {
        string s; cin >> s;
        for (int j = 0; j < ptW; j++) ptArr[i][j] = s[j];
    }
    for (int i = 0; i < scH; i++) {
        string s; cin >> s;
        for (int j = 0; j < scW; j++) scArr[i][j] = s[j];
    }
    getPow1();
    getPow2();
    rabinKarp();
    cout << ans;
    return 0;
}