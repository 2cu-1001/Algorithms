#include <bits/stdc++.h>
using namespace std;
int N, minAnsDiff = -1, arr[60];
vector<int> ans;
void solve()
{
	sort(&arr[1], &arr[N + 1]);
	ans.push_back(arr[1]);
	
	for (int i = 2; i <= N; i++) {
		int curSz = i - 1, insertIdx = 0,
			curVal = arr[i], minDiff = INT_MAX;
		for (int j = 0; j < curSz; j++) {
			int curDiff = max(abs(curVal - ans[j]), abs(curVal - ans[(j + 1) % curSz]));
			if (curDiff <= minDiff) { minDiff = curDiff, insertIdx = j; }
		}
		auto it = ans.begin() + insertIdx + 1;
		ans.insert(it, curVal);
	}
	for (int i = 0; i < N - 1; i++) minAnsDiff = max(minAnsDiff, abs(ans[i + 1] - ans[i]));
	minAnsDiff = max(minAnsDiff, abs(ans[N - 1] - ans[0]));

	ans.clear();
	ans.push_back(arr[1]);

	for (int i = 2; i <= N; i++) {
		int curSz = i - 1, insertIdx = 0, curVal = arr[i];
		for (int j = 0; j < curSz; j++) {
			int curDiff = max(abs(curVal - ans[j]), abs(curVal - ans[(j + 1) % curSz]));
			if (curDiff <= minAnsDiff) insertIdx = j;
		}
		auto it = ans.begin() + insertIdx + 1;
		ans.insert(it, curVal);
	}

	for (int i : ans) cout << i << " ";
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> N;
	for (int i = 1; i <= N; i++) cin >> arr[i];
	solve();
}