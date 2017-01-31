// Copyright 2016 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
const int N = 1005;  // left max
const int M = 1005;  // right max
const double EPS = 1e-8;
typedef int T;
const T INF = 0x3f3f3f3f;
T lj[N][M];
int n, m;  // left, right num
class KM {
 private:
     T slack[M];
     int llink[N], rlink[M];  // left link to right, right link to left
     T fl[N], fr[M];  // flag num
     int lused[N], rused[M];  // record used point in a dfs
     bool dfs(int k) {  // find a method that can make k link to right
         lused[k] = 1;
         for (int i = 1; i <= m; i++) {
             if (lj[k][i] == -INF || rused[i]) continue;
             T tmp = fl[k] + fr[i] - lj[k][i];
             if (fabs(tmp) < EPS) {
                 rused[i] = 1;
                 if (rlink[i] == -1 || dfs(rlink[i])) {
                     rlink[i] = k;  // make or change link
                     llink[k] = i;
                     return true;
                 }
             } else if (slack[i] > tmp) {
                 slack[i] = tmp;
             }
         }
         return false;
     }
 public:
     KM() {
         fill(llink, llink + n + 1, -1);
         fill(rlink, rlink + m + 1, -1);
         fill(fr, fr + m + 1, 0);
         fill(fl, fl + n + 1, -INF);
         for (int i = 1; i <= n; i++) {
             for (int j = 1; j <= m; j++) {
                 if (fl[i] < lj[i][j]) fl[i] = lj[i][j];
             }
         }
     }
     T get_result() {
         int flag = 1;
         for (int d = 1; d <= n; d++) {
             fill(slack, slack + m + 1, INF);
             while (1) {
                 fill(lused, lused + n + 1, 0);
                 fill(rused, rused + m + 1, 0);
                 if (dfs(d)) break;
                 T e = INF;
                 for (int i = 1; i <= m; i++) {  // min slack
                     if (!rused[i] && e > slack[i]) e = slack[i];
                 }
                 if (e == INF) {
                     flag = 0;
                     break;
                 }
                 for (int i = 1; i <= n; i++) {
                     if (lused[i]) fl[i] -= e;
                 }
                 for (int i = 1; i <= m; i++) {
                     if (rused[i]) fr[i] += e;
                     else if (lj[d][i] != -INF) slack[i] -= e;
                 }
             }
             if (flag == 0) break;
         }
         if (flag) {
             T res = 0;
             for (int i = 1; i <= n; i++) {
                 res += lj[i][llink[i]];
             }
             return res;
         } else return -1;
     }
     ~KM() {}
};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int k;
    while (cin >> n >> m >> k) {
        // init
        for (int i = 1; i <= n; i++) fill(lj[i], lj[i] + m + 1, -INF);
        for (int i = 1; i <= k; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            lj[u][v] = w;
        }
        KM *a = new KM();
        cout << a->get_result() << "\n";
        delete a;
    }
}
