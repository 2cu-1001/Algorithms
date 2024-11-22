#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
int N, M, K, curAns, arr[100010], ch[100010], cch[100010];
vector<pair<pair<int, int>, int>> q;
vector<pair<int, int>> ans;
bool cmp(pair<pair<int, int>, int> p1, pair<pair<int, int>, int> p2)
{
	if (p1.x.x / K == p2.x.x / K) return p1.x.y < p2.x.y;
	return p1.x.x / K < p2.x.x / K;
}
void solve()
{
	K = sqrt(N);
	sort(q.begin(), q.end(), cmp);
	int st = -1, ed = -1, curSt, curEd, curV;
	curAns = 0;

	cch[0] = 100000;
	for (auto curQ : q) {
		tie(curSt, curEd) = curQ.x;
		if (st == -1 && ed == -1) {
			for (int i = curSt; i <= curEd; i++) {
				curV = arr[i];
				cch[ch[curV]]--;
				ch[curV]++; cch[ch[curV]]++;
				curAns = max(ch[curV], curAns);
			}
			st = curSt; ed = curEd;
		}
		else {
			if (st < curSt)
				for (int i = st; i < curSt; i++) {
					curV = arr[i];

					cch[ch[curV]]--;
					if (cch[curAns] == 0 && ch[curV] == curAns) curAns--;
					ch[curV]--; cch[ch[curV]]++;
				}
			else if (st > curSt)
				for (int i = curSt; i < st; i++) {
					curV = arr[i];

					cch[ch[curV]]--;
					ch[curV]++; cch[ch[curV]]++;
					curAns = max(curAns, ch[curV]);
				}

			if (ed < curEd)
				for (int i = ed + 1; i <= curEd; i++) {
					curV = arr[i];

					cch[ch[curV]]--;
					ch[curV]++; cch[ch[curV]]++;
					curAns = max(curAns, ch[curV]);
				}
			else if (ed > curEd)
				for (int i = curEd + 1; i <= ed; i++) {
					curV = arr[i];

					cch[ch[curV]]--;
					if (cch[curAns] == 0 && ch[curV] == curAns) curAns--;
					ch[curV]--; cch[ch[curV]]++;
				}
			st = curSt; ed = curEd;
		}
		ans.push_back({ curQ.y, curAns });
	}
	sort(ans.begin(), ans.end());
	for (auto c : ans) cout << c.y << "\n";
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 1; i <= N; i++) cin >> arr[i];
	cin >> M;
	for (int i = 1; i <= M; i++) {
		int st, ed; cin >> st >> ed;
		q.push_back({ { st, ed }, i });
	}
	solve();
}