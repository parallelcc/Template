// Copyright 2016 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
#define N 1005  // right max
#define M 1005  // left max
vector<vector<int> > lj(M);  // from left to right
int k, m, n;  // edge, left, right
int link[N + M];  // every point's link
int pre[M];  // left's last left in a bfs
int used[N];  // record used right point in a dfs
int hungary() {
    int ans = 0;
    fill(link, link + N + m + 1, -1);
    fill(used, used + n + 1, -1);
    for (int i = 1; i <= m; i++) {
        if (link[N + i] == -1) {
            queue<int> q;
            q.push(i);
            pre[i] = -1;
            bool flag = 0;
            while (!q.empty() && !flag) {
                int u = q.front();
                q.pop();
                for (int j = 0; j < lj[u].size(); j++) {
                    int v = lj[u][j];
                    if (used[v] != i) {
                        used[v] = i;
                        if (link[v] != -1) {
                            q.push(link[v]);
                            pre[link[v]] = u;
                        } else {
                            flag = 1;
                            while (u != -1) {
                                int temp = link[N + u];
                                link[v] = u;
                                link[N + u] = v;
                                u = pre[u];
                                v = temp;
                            }
                            break;
                        }
                    }
                }
            }
        }
        if (link[N + i] != -1) ans++;
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while (cin >> k >> m >> n) {
        // init
        for (int i = 1; i <= m; i++) lj[i].clear();
        for (int i = 0; i < k; i++) {
            int u, v;
            cin >> u >> v;
            lj[u].push_back(v);
        }
        // main program
        cout << hungary() << '\n';
    }
}
