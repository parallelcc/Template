// Copyright 2016 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
const int MAXN = 1010;
const int INF = 0x3f3f3f3f;
struct Edge{
    int v;
    int cost, cap, rev;
    Edge(int v, int cap, int cost, int rev) {
        this->v = v;
        this->cap = cap;
        this->cost = cost;
        this->rev = rev;
    }
};
vector<vector<Edge> > E(MAXN);
bool vis[MAXN];
int cnt[MAXN];
int dist[MAXN];
pair<int, int> pre[MAXN];
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
    pre[start] = make_pair(-1, 0);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        vis[u] = false;
        for (int i = 0; i < E[u].size(); i++) {
            int v = E[u][i].v;
            if (E[u][i].cap && dist[v] > dist[u] + E[u][i].cost) {
                dist[v] = dist[u] + E[u][i].cost;
                pre[v] = make_pair(u, i);
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
int minCostMaxflow(int s, int t, int &cost) {
    int flow = 0;
    cost = 0;
    while (SPFA(s, t)) {
        int Min = INF;
        for (int i = t; pre[i].first != -1; i = pre[i].first) {
            if (Min > E[pre[i].first][pre[i].second].cap) {
                Min = E[pre[i].first][pre[i].second].cap;
            }
        }
        for (int i = t; pre[i].first != -1; i = pre[i].first) {
            Edge &k = E[pre[i].first][pre[i].second];
            k.cap -= Min;
            E[i][k.rev].cap += Min;
            cost += k.cost * Min;
        }
        flow += Min;
    }
    return flow;
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
            int u, v, w, c;
            cin >> u >> v >> w >> c;
            E[u].push_back(Edge(v, w, c, E[v].size()));
            E[v].push_back(Edge(u, 0, -c, E[u].size() - 1));
        }
        int cost;
        int flow = minCostMaxflow(S, N, cost);
        cout << flow << ' ' << cost << '\n';
    }
    return 0;
}
