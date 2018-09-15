#include <bits/stdc++.h>
using namespace std;
using T = int;

struct node {
    int v;
    T w;
};
class HDL {
  private:
    vector<pair<int, int>> a;

  public:
    static const int MAXN = 100005;
    int fa[MAXN], son[MAXN], top[MAXN], dep[MAXN], num[MAXN], p[MAXN];
    //static int fp[MAXN];
    HDL(vector<vector<node>>& lj, int r/*, vector<T>& bq, vector<T>& dis*/) {
        int n = lj.size();
        int pos = 0;
        dep[r] = 0;
        memset(son, -1, sizeof(int) * n);
        a.reserve(n);
        function<void(int, int)> dfs = [&](int k, int pre) {
            fa[k] = pre;
            dep[k] = dep[pre] + 1;
            num[k] = 1;
            for (auto& i : lj[k]) {
                if (i.v != pre) {
                    //dis[i.v] = dis[k] + i.w;
                    dfs(i.v, k);
                    num[k] += num[i.v];
                    if (son[k] == -1 || num[i.v] > num[son[k]]) son[k] = i.v;
                } else {
                    //bq[i.v] = i.w;
                }
            }
        };
        function<void(int, int)> getpos = [&](int k, int t) {
            top[k] = t;
            p[k] = pos++;
            //fp[p[k]] = k;
            if (son[k] == -1) return;
            getpos(son[k], t);
            for (auto& i : lj[k]) {
                if (i.v != son[k] && i.v != fa[k]) getpos(i.v, i.v);
            }
        };
        dfs(r, r);
        getpos(r, r);
    }
    int LCA(int u, int v) {
        for (; top[u] != top[v]; dep[top[u]] > dep[top[v]]?u = fa[top[u]] : v = fa[top[v]]);
        return dep[u] < dep[v]? u : v;
    }
    const vector<pair<int, int>>& path(int u, int v) {  // [,]
        a.clear();
        int f1 = top[u], f2 = top[v];
        while (f1 != f2) {
            if (dep[f1] < dep[f2]) {
                swap(f1, f2);
                swap(u, v);
            }
            a.emplace_back(p[f1], p[u] + 1);
            u = fa[f1];
            f1 = top[u];
        }
        if (dep[u] > dep[v]) swap(u, v);
        a.emplace_back(p[u], p[v] + 1);  // point
        // if (u != v) a.emplace_back(p[u] + 1, p[v] + 1);  // edge
        return a;  // [,)
    }
};
