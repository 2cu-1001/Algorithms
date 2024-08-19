#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define x first
#define y second
using namespace std;
int N, Q, K, arr[1000010], ch[1000010];
vector<int> v;
vector<pair<int, int>> ans;
vector<pair<pair<int, int>, int>> q;
bool cmp(pair<pair<int,int>, int> &p1, pair<pair<int,int>, int> &p2)
{
	if (p1.x.x / K == p2.x.x / K) return p1.x.y < p2.x.y;
	return p1.x.x / K < p2.x.x / K;
}
void solve()
{
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	for (int i = 1; i <= N; i++) {
		int curIdx = lower_bound(v.begin(), v.end(), arr[i]) - v.begin();
		arr[i] = curIdx + 1;
	}

	K = sqrt(N);
	sort(q.begin(), q.end(), cmp);

	int st = -1, ed = -1, curAns = 0, curSt, curEd;
	for (auto curQ : q) {
		tie(curSt, curEd) = curQ.x;
		if (st == -1 && ed == -1) {
			for (int i = curSt; i <= curEd; i++) {
				if (!ch[arr[i]]) curAns++;
				ch[arr[i]]++;
			}
		}
		else {
			if (curSt < st) 
				for (int i = curSt; i < st; i++) {
					if (!ch[arr[i]]) curAns++;
					ch[arr[i]]++;
				}
			else if (curSt > st) 
				for (int i = st; i < curSt; i++) {
					ch[arr[i]]--;
					if (!ch[arr[i]]) curAns--;
				}

			if (curEd < ed) 
				for (int i = curEd + 1; i <= ed; i++) {
					ch[arr[i]]--;
					if (!ch[arr[i]]) curAns--;
				}
			else if (curEd > ed) 
				for (int i = ed + 1; i <= curEd; i++) {
					if (!ch[arr[i]]) curAns++;
					ch[arr[i]]++;
				}
		}
		st = curSt, ed = curEd;
		ans.push_back({ curQ.y, curAns });
	}
	sort(ans.begin(), ans.end());
	for (auto cur : ans) cout << cur.y << "\n";
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> arr[i]; v.push_back(arr[i]);
	}
	cin >> Q;
	for (int i = 1; i <= Q; i++) {
		int s, e; cin >> s >> e;
		q.push_back({ { s, e }, i });
	}
	solve();
}