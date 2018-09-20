#include <bits/stdc++.h>
using namespace std;
using T = int;

struct edge {
    int v;
    T w;
};
template <size_t N = 100005>
class HDL {
  private:
    struct node {
        int fa, son, top, dep, num, p;
    };
    vector<pair<int, int>> a;

  public:
    static node tr[N];
    //static int fp[N];
    HDL(vector<vector<edge>>& lj, int r/*, vector<T>& bq, vector<T>& dis*/) {
        int n = lj.size();
        int pos = 0;
        tr[r].dep = 0;
        for (int i = 0; i < n; i++) tr[i].son = -1;
        a.reserve(n);
        function<void(int, int)> dfs = [&](int k, int pre) {
            tr[k].fa = pre;
            tr[k].dep = tr[pre].dep + 1;
            tr[k].num = 1;
            for (auto& i : lj[k]) {
                if (i.v != pre) {
                    //dis[i.v] = dis[k] + i.w;
                    dfs(i.v, k);
                    tr[k].num += tr[i.v].num;
                    if (tr[k].son == -1 || tr[i.v].num > tr[tr[k].son].num) tr[k].son = i.v;
                } else {
                    //bq[i.v] = i.w;
                }
            }
        };
        function<void(int, int)> getpos = [&](int k, int t) {
            tr[k].top = t;
            tr[k].p = pos++;
            //fp[tr[k].p] = k;
            if (tr[k].son == -1) return;
            getpos(tr[k].son, t);
            for (auto& i : lj[k]) {
                if (i.v != tr[k].son && i.v != tr[k].fa) getpos(i.v, i.v);
            }
        };
        dfs(r, r);
        getpos(r, r);
    }
    int LCA(int u, int v) {
        for (; tr[u].top != tr[v].top; tr[tr[u].top].dep > tr[tr[v].top].dep?u = tr[tr[u].top].fa : v = tr[tr[v].top].fa);
        return tr[u].dep < tr[v].dep? u : v;
    }
    const vector<pair<int, int>>& path(int u, int v) {  // [,]
        a.clear();
        int f1 = tr[u].top, f2 = tr[v].top;
        while (f1 != f2) {
            if (tr[f1].dep < tr[f2].dep) {
                swap(f1, f2);
                swap(u, v);
            }
            a.emplace_back(tr[f1].p, tr[u].p + 1);
            u = tr[f1].fa;
            f1 = tr[u].top;
        }
        if (tr[u].dep > tr[v].dep) swap(u, v);
        a.emplace_back(tr[u].p, tr[v].p + 1);  // point
        // if (u != v) a.emplace_back(tr[u].p + 1, tr[v].p + 1);  // edge
        return a;  // [,)
    }
};
template<size_t N> struct HDL<N>::node HDL<N>::tr[N];
//template<size_t N> int HDL<N>::fp[N];
