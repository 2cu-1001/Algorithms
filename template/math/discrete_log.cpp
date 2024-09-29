void discerete_log()
{
    // B ^ L == N (mod P)
    // L = i * m + j
    m = ceil(sqrt(P - 1));
    inverse = EEA(B, P);
    
    int curPow = 1;
    for (int j = 0; j <= m; j++) {
        int cur = (N * curPow) % P;
        h.insert({ cur, j });
        curPow = (curPow * inverse) % P;
    }

    int mPow = 1;
    for (int i = 1; i <= m; i++) mPow = (mPow * B) % P;

    curPow = 1;
    for (int i = 0; i <= m; i++) {
        auto it = h.find(curPow);
        if (it != h.end()) {
            cout << ((i * m) % P + it->second) % P << "\n";
            return;
        }
        curPow = (curPow * mPow) % P;
    }
}