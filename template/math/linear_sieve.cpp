void linearSieve(int mpf[sz], int isP[sz], vector<int> P)
{
    //mpf : minimum prime factor
    memset(mpf, -1, sizeof(mpf));
    for (int i = 2; i <= 2001; i++) {
        if (mpf[i] == -1) {
            mpf[i] = i; P.push_back(i);
            isP[i] = 1;
        }
        for (int p : P) {
            int x = i * p;
            if (x > 2001) break;
            mpf[x] = p;
            if (i % p == 0) break;
        }
    }
}