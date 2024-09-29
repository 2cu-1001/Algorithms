void getmCm(int M)
{
	for (int i = 0; i <= M; i++)
		for (int j = 0; j <= i; j++) {
			if (i == j || j == 0) mcm[i][j] = 1;
			else mcm[i][j] = (mcm[i - 1][j] + mcm[i - 1][j - 1]) % M;
		}
}
int solve(int M, int N, int K, int mcm[SZ][SZ])
{
    //nCk mod m
	int ret = 1;
	getmCm(M);
	while (N != 0 || K != 0) {
		ret = (ret * mcm[N % M][K % M]) % M;
		N /= M; K /= M;
	}
	return ret;
}