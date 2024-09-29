void DFS(int n)
{
    ch[n] = 1;
    for (int nxt : adj[n]) {
        if (ch[nxt] == 1) continue;
        DFS(nxt);
    }
    st.push(n);
    return;
}
void RDFS(int n, vector<int>(&tmp), int sccCnt)
{
    ch[n] = 1;
    for (int nxt : radj[n]) {
        if (ch[nxt] == 1) continue;
        tmp.push_back(nxt);
        sccNum[nxt] = sccCnt;
        RDFS(nxt, tmp, sccCnt);
    }
    return;
}
void kosaraju()
{
    //radj 때메 2*N까지
    for (int i = 1; i <= 2 * N; i++) {
        if (ch[i] == 1) continue;
        DFS(i);
    }
    memset(ch, 0, sizeof(ch));
    int sccCnt = 1;
    while (!st.empty()) {
        int cur = st.top();
        st.pop();
        if (ch[cur] == 1) continue;
        vector<int> tmp;
        tmp.push_back(cur);
        sccNum[cur] = sccCnt;
        RDFS(cur, tmp, sccCnt);
        sort(tmp.begin(), tmp.end());
        ans.push_back(tmp);
        sccCnt++;
    }
}