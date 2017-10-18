// Copyright 2016 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
using T = int;
using L = int;
const int INF = 0x3f3f3f3f;
class minCost {
 private:
     struct node{
         int v;
         L cap;
         T cost;
         int rev;
     };
     vector<vector<node>> lj;
     vector<bool> vis;
     vector<int> cnt, pre;
     vector<T> dis;
     bool SPFA(int start, int end) {
         fill(dis.begin(), dis.end(), INF);
         fill(vis.begin(), vis.end(), 0);
         fill(cnt.begin(), cnt.end(), 0);
         vis[start] = true;
         dis[start] = 0;
         queue<int> que;
         que.push(start);
         cnt[start] = 1;
         pre[start] = -1;
         while (!que.empty()) {
             int u = que.front();
             que.pop();
             vis[u] = false;
             for (auto& i : lj[u]) {
                 if (i.cap && dis[i.v] > dis[u] + i.cost) {
                     dis[i.v] = dis[u] + i.cost;
                     pre[i.v] = i.rev;
                     if (!vis[i.v]) {
                         vis[i.v] = true;
                         que.push(i.v);
                         if (++cnt[i.v] > n) return false;
                     }
                 }
             }
         }
         // if (dis[end] >= 0) return false; // not maxFlow
         if (dis[end] == INF) return false;
         return true;
     }

 public:
     int n;
     minCost() {}
     minCost(int n) : n(n) {
         lj.resize(n);
         vis.resize(n);
         cnt.resize(n);
         dis.resize(n);
         pre.resize(n);
     }
     void add(int u, int v, L w, T c) {
         lj[u].push_back({v, w, c, lj[v].size()});
         lj[v].push_back({u, 0, -c, lj[u].size() - 1});
     }
     pair<L, T> solve(int s, int t) {
         L flow = 0;
         T cost = 0;
         while (SPFA(s, t)) {
             L Min = INF;
             for (int i = t; pre[i] != -1; i = lj[i][pre[i]].v) {
                 auto& j = lj[i][pre[i]];
                 Min = min(Min, lj[j.v][j.rev].cap);
             }
             for (int i = t; pre[i] != -1; i = lj[i][pre[i]].v) {
                 auto& j = lj[i][pre[i]];
                 auto& k = lj[j.v][j.rev];
                 k.cap -= Min;
                 j.cap += Min;
             }
             cost += dis[t] * Min;
             flow += Min;
         }
         return {flow, cost};
     }
};
