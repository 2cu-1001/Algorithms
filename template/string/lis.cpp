void LIS(int n, vector<int> d)
{
	for (int i = 0; i < n; i++) {
		if (d.empty()) {
			d.push_back(arr[i]);
			ans++;
		}
		else {
			auto it = lower_bound(d.begin(), d.end(), arr[i]);
			if (it == d.end()) {
				d.push_back(arr[i]);
				ans++;
			}
			else *it = arr[i];
		}
	}
}