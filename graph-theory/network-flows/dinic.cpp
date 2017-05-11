#include <bits/stdc++.h>
using namespace std;
using T = int;
const T INF = 0x3f3f3f3f;
class dinic {
 private:
     struct node {
         int num;
         T cap;
         int rev;
     };
     vector<vector<node>> lj;
     vector<int> dis, cur;
     int s, d;
     int bfs() {
         fill(dis.begin(), dis.end(), 0);
         dis[s] = 1;
         queue<int> q;
         q.push(s);
         while (!q.empty()) {
             int p = q.front();
             q.pop();
             for (auto &i : lj[p]) {
                 if (!dis[i.num] && i.cap > 0) {
                     dis[i.num] = dis[p] + 1;
                     if (i.num == d) return 1;
                     q.push(i.num);
                 }
             }
         }
         return 0;
     }
     T dfs(int p, T low = INF) {
         if (p == d) return low;
         T flow = 0;
         for (int &i = cur[p]; i < lj[p].size(); i++) {
             auto &j = lj[p][i];
             if (dis[j.num] == dis[p] + 1 && j.cap > 0) {
                 int k = dfs(j.num, min(low, j.cap));
                 j.cap -= k;
                 lj[j.num][j.rev].cap += k;
                 flow += k;
                 low -= k;
                 if (low == 0) break;
             }
         }
         return flow;
     }

 public:
     dinic(int n) {
         lj.resize(n);
         dis.resize(n);
         cur.resize(n);
     }
     void add(int u, int v, int w) {
         lj[u].push_back({v, w, lj[v].size()});
         lj[v].push_back({u, 0, lj[u].size() - 1});
     }
     T solve(int s, int d) {
         T ans = 0;
         this->s = s;
         this->d = d;
         while (bfs()) {
             fill(cur.begin(), cur.end(), 0);
             ans += dfs(s);
         }
         return ans;
     }
};
