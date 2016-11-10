// Copyright 2016 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
#define N 1005  // right max
#define M 1005  // left max
#define INF 0x3f3f3f3f
int lj[M][N];
int slack[N];
int link[N], fl[M], fr[N];  // right link to left
int lused[M], rused[N];  // record used point in a dfs
int m, n;  // left, right num
bool dfs(int k) {  // find a method that can make k link to right
    lused[k] = 1;
    for (int i = 1; i <= n; i++) {
        if (lj[k][i] == -INF || rused[i]) continue;
        int tmp = fl[k] + fr[i] - lj[k][i];
        if (!tmp) {
            rused[i] = 1;
            if (link[i] == -1 || dfs(link[i])) {
                link[i] = k;  // make or change link
                return true;
            }
        } else if (slack[i] > tmp) {
            slack[i] = tmp;
        }
    }
    return false;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int k;
    while (cin >> m >> n >> k) {
        // init
        fill(link, link + n + 1, -1);
        fill(fr, fr + n + 1, 0);
        fill(fl, fl + n + 1, -INF);
        for (int i = 1; i <= m; i++) fill(lj[i], lj[i] + n + 1, -INF);
        for (int i = 1; i <= k; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            lj[u][v] = w;
            if (fl[i] < w) fl[i] = w;
        }
        // main program
        int flag = 1;
        for (int d = 1; d <= m; d++) {
            fill(slack, slack + n + 1, INF);
            while (1) {
                fill(lused, lused + m + 1, 0);
                fill(rused, rused + n + 1, 0);
                if (dfs(d)) break;
                int e = INF;
                for (int i = 1; i <= n; i++) {  // min slack
                    if (!rused[i] && e > slack[i]) e = slack[i];
                }
                if (e == INF) {
                    flag = 0;
                    break;
                }
                for (int i = 1; i <= m; i++) {
                    if (lused[i]) fl[i] -= e;
                }
                for (int i = 1; i <= n; i++) {
                    if (rused[i]) fr[i] += e;
                    else if (lj[d][i] != -INF) slack[i] -= e;
                }
            }
            if (flag == 0) break;
        }
        if (flag) {
            int res = 0;
            for (int i = 1; i <= n; i++) {
                if (link[i] != -1) res += lj[link[i]][i];
            }
            cout << res << '\n';
        }  // else cout << -1 << '\n';
    }
}
