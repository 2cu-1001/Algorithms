#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll C, N, T, p, a, lenCh[50][2010], apow[2010];
unordered_set<ll> cs[50], ns[50];
ll rabinKarp(string& s)
{
	ll curHash = 0;
	int len = (int)s.length();
	for (int i = 0; i < len; i++) {
		curHash = ((curHash * a) % p + s[i]) % p;
	}

	return curHash;
}
void getPow()
{
	apow[0] = 1;
	for (int i = 1; i <= 2001; i++) apow[i] = (apow[i - 1] * a) % p;
}
void solve()
{
	p = 400000000;
	a = 43;
	getPow();

	string s; ll curRes;
	for (int i = 1; i <= C; i++) {
		cin >> s; curRes = rabinKarp(s);
		cs[s[0] - 'a' + 1].insert(curRes);
	}
	for (int i = 1; i <= N; i++) {
		cin >> s; curRes = rabinKarp(s);
		ns[s[0] - 'a' + 1].insert(curRes);
	}

	cin >> T;
	while (T--) {
		cin >> s;
		int len = (int)s.length(), isOk = 0;
		ll curHash = 0, curTotHash = rabinKarp(s);

		for (int i = 0; i < min(len, 1001); i++) {
			if (isOk) break;

			curHash = ((curHash * a) % p + s[i]) % p;
			int idx1 = s[0] - 'a' + 1;

			auto itc = cs[idx1].find(curHash);
			if (itc != cs[idx1].end()) {
				ll nxtHash = ((curTotHash - ((curHash * apow[len - i - 1]) % p)) + p) % p;

				if (i + 1 >= s.length()) continue;
				int idx2 = s[i + 1] - 'a' + 1;

				auto itn = ns[idx2].find(nxtHash);
				if (itn != ns[idx2].end()) { isOk = 1; cout << "Yes\n"; }
			}
		}
		if (!isOk) cout << "No\n";
	}
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> C >> N;
	solve();
}