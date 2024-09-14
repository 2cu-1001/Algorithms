#include <bits/stdc++.h>
using namespace std;
int N;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N;
    cout << (N == 1 ? 1 : N / 2) << "\n";
    for (int i = 1; i <= N; i++) cout << max(i / 2, 1) << " ";
}