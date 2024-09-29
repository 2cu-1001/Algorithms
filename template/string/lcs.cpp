void LCS(int l1, int l2, string s1, string s2, int length, int d[sz][sz], vector<cahr> lcs)
{
	for (int i = 1; i <= l1; i++) {
		for (int j = 1; j <= l2; j++) {
			if (s1[i - 1] == s2[j - 1]) d[i][j] = d[i - 1][j - 1] + 1;
			else d[i][j] = max(d[i][j - 1], d[i - 1][j]);
		}
	}

	length = -1;
	for (int i = 1; i <= l1; i++) {
		for (int j = 1; j <= l2; j++)
			if (d[i][j] > length) length = d[i][j];
	}
	int x = l1; int y = l2;

	while (1) {
		if (d[l1][l2] == 0) break;
		if (d[l1][l2] == d[l1 - 1][l2])
			l1--;
		else if (d[l1][l2] == d[l1][l2 - 1])
			l2--;
		else {
			lcs.push_back(s1[l1 - 1]);
			l1--; l2--;
		}
	}
}