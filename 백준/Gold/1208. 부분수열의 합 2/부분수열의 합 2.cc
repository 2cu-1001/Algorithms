#include <bits/stdc++.h>
#include <unordered_map>
#define ll long long
using namespace std;
ll n, s, sum, ans, sz1, sz2;
ll arr1[40], arr2[40], ch1[40], ch2[40];
unordered_map<ll, ll> m;
void solve(ll sz, int arr)
{
	ll tmp_sum = 0;
	if (arr == 1)
	{
		for (int i = 0; i < sz; i++)
		{
			if (ch1[i] == 1)
			{
				tmp_sum += arr1[i];
			}
		}
		if (m.find(tmp_sum) != m.end())
		{
			m.find(tmp_sum)->second = m.find(tmp_sum)->second + 1;
		}
		else m.insert({ tmp_sum, 1 });
	}
	else if (arr == 2)
	{
		for (int i = 0; i < sz; i++)
		{
			if (ch2[i] == 1)
			{
				tmp_sum += arr2[i];
			}
		}
		if (m.find(s - tmp_sum) != m.end())
			ans += m.find(s - tmp_sum)->second;
	}
}
void comb(int cnt, int sz, int arr)
{
	if (cnt == sz)
	{
		solve(sz, arr);
		return;
	}
	for (int i = 0; i < 2; i++)
	{
		if (arr == 1)
		{
			ch1[cnt] = i;
			comb(cnt + 1, sz, arr);
		}
		else if (arr == 2)
		{
			ch2[cnt] = i;
			comb(cnt + 1, sz, arr);
		}
	}
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> s;
	sz1 = n / 2;
	sz2 = n - (n / 2);
	for (int i = 0; i < sz1; i++)
		cin >> arr1[i];
	for (int i = 0; i < sz2; i++)
		cin >> arr2[i];
	comb(0, sz1, 1);
	comb(0, sz2, 2);
	if (s == 0) cout << ans - 1;
	else cout << ans;
}