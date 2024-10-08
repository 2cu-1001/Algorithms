int DFS(int cur)
{
	for (auto nxt : adj[cur]) {
		if (ch[nxt]) continue;
		ch[nxt] = 1;
		if (!assign[nxt] || DFS(assign[nxt])) {
			assign[nxt] = cur; return 1;
		}
	}
	return 0;
}
void bipartite_matching()
{
    int ret;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j <= N + 1; j++) ch[j] = 0;
		if (DFS(i)) ret++;
        if (ret >= M) break;
	}
	return ret;
}
