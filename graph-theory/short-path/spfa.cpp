// Copyright 2016 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
const int MAXN = 1010;
const int INF = 0x3f3f3f3f;
struct Edge{
    int v;
    int cost;
    Edge(int _v = 0, int _cost = 0):v(_v), cost(_cost){}
};
vector<vector<Edge> > E(MAXN);
bool vis[MAXN];
int cnt[MAXN];
int dist[MAXN];
int pre[MAXN];
int n, m;
bool SPFA(int start, int end) {
    fill(dist, dist + n + 1, INF);
    fill(vis, vis + n + 1, 0);
    fill(cnt, cnt + n + 1, 0);
    vis[start] = true;
    dist[start] = 0;
    queue<int> que;
    que.push(start);
    cnt[start] = 1;
    pre[start] = -1;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        vis[u] = false;
        for (int i = 0; i < E[u].size(); i++) {
            int v = E[u][i].v;
            if (dist[v] > dist[u] + E[u][i].cost) {
                dist[v] = dist[u] + E[u][i].cost;
                pre[v] = u;
                if (!vis[v]) {
                    vis[v] = true;
                    que.push(v);
                    if (++cnt[v] > n) return false;
                }
            }
        }
    }
    if (dist[end] == INF) return false;
    return true;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while (cin >> n >> m) {
        int S, N;
        S = 1;
        N = n;
        for (int i = 0; i < n + 1; i++) E[i].clear();
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            E[u].push_back(Edge(v, w));
            E[v].push_back(Edge(u, w));
        }
        if (SPFA(S, N)) cout << dist[N] << '\n';
        // else cout << -1 << '\n';
    }
    return 0;
}
