#include <bits/stdc++.h>
using namespace std;
template <typename T, class op = less<pair<T, int>>>
struct RMQ {
    vector<vector<pair<T, int>>> dp;
    RMQ() {}
    RMQ(vector<T>& a) {
        int n = a.size();
        int m = __lg(n) + 1;
        dp.resize(n);
        for (int i = 0; i < n; i++) {
            dp[i].resize(m);
            dp[i][0] = {a[i], i};
        }
        for (int j = 1; j < m; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1], op());
            }
        }
    }
    pair<T, int> que(int l, int r) {
        int k = 31 - __builtin_clz(r - l);
        return min(dp[l][k], dp[r - (1 << k)][k], op());
    }
};

using T = int;
struct node {
    int v;
    T w;
};
struct LCA {
    vector<int> dep, pos, olx;
    vector<T> dis;
    RMQ<int> st;
    LCA(vector<vector<node>>& lj, int r) {
        int n = lj.size();
        dep.reserve(2 * n);
        olx.reserve(2 * n);
        pos.resize(n);
        dis.resize(n);
        function<void(int, int)> dfs = [&](int k, int pre) {
            pos[k] = olx.size();
            olx.push_back(k);
            dep.push_back(dep.size() ? dep.back() + 1 : 1);
            for (auto& i : lj[k]) {
                if (i.v != pre) {
                    dis[i.v] = dis[k] + i.w;
                    dfs(i.v, k);
                    olx.push_back(k);
                    dep.push_back(dep.back() - 1);
                }
            }
        };
        dfs(r, r);
        st = RMQ<int>(dep);
    }
    int que(int u, int v) {
        if (pos[u] > pos[v]) swap(u, v);
        return olx[st.que(pos[u], pos[v] + 1).second];
    }
};
