void dijkstra()
{
    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        if (dist[cur.y] != cur.x) continue;
        for (auto nxt : adj[cur.y]) {
            if (dist[nxt.y] > dist[cur.y] + nxt.x) {
                dist[nxt.y] = dist[cur.y] + nxt.x;
                pq.push({ dist[nxt.y], nxt.y });
            }
        }
    }
}
