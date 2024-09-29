int DFS(int cur, int root)
{
	ch[cur] = 1; disc[cur] = ++cnt;
	int curRet = disc[cur], gotRet, chdCnt = 0, isOk = 0;

	for (int nxt : adj[cur]) {
		if (ch[nxt]) {
			curRet = min(curRet, disc[nxt]); continue;
		}

		gotRet = DFS(nxt, root); chdCnt++;
		if (disc[cur] <= gotRet && cur != root) isOk = 1;
		curRet = min(curRet, gotRet);
	}
	if (isOk) ans.push_back(cur);

	if (cur == root && chdCnt > 1 && !isOk) ans.push_back(cur);
	return curRet;
}
void articulation()
{
	for (int i = 1; i <= V; i++) {
		if (ch[i]) continue;		
		DFS(i, i);
	}
}