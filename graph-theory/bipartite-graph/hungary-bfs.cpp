// Copyright 2016 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
const int N = 1005;  // left max
const int M = 1005;  // right max
vector<int> lj[N];  // from left to right
int n, m;  // left, right
class hungary {
 private:
     int llink[N], rlink[M];  // every point's link
     int pre[N];  // left's last left in a bfs
     int used[M];  // record used right point in a dfs

 public:
     int get_result() {
         int ans = 0;
         for (int i = 1; i <= n; i++) {
             if (llink[i] == -1) {
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
                             if (rlink[v] != -1) {
                                 q.push(rlink[v]);
                                 pre[rlink[v]] = u;
                             } else {
                                 flag = 1;
                                 while (u != -1) {
                                     int temp = llink[u];
                                     rlink[v] = u;
                                     llink[u] = v;
                                     u = pre[u];
                                     v = temp;
                                 }
                                 break;
                             }
                         }
                     }
                 }
             }
             if (llink[i] != -1) ans++;
         }
         return ans;
     }
     hungary() {
         fill(llink, llink + n + 1, -1);
         fill(rlink, rlink + m + 1, -1);
         fill(used, used + n + 1, -1);
     }
     ~hungary() {}
};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int k;
    while (cin >> k >> n >> m) {
        for (int i = 0; i <= n; i++) lj[i].clear();
        for (int i = 0; i < k; i++) {
           int u, v;
           cin >> u >> v;
           lj[u].push_back(v);
        }
        hungary *a = new hungary();
        cout << a->get_result() << '\n';
        delete a;
    }
}
