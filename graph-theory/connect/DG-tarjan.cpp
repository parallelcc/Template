// Copyright 2017 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
vector<vector<int>> tarjan(const vector<vector<int>> &lj) {
    int n = lj.size();
    vector<int> dfn(n), low(n), bh(n, -1);
    int ind = 1;
    int num = 0;
    stack<int, vector<int>> s;
    function<void(int)> dfs = [&](int k) {
        dfn[k] = low[k] = ind++;
        s.push(k);
        for (auto i : lj[k]) {
            if (!dfn[i]) {
                dfs(i);
                low[k] = min(low[k], low[i]);
            } else if (bh[i] == -1)
                low[k] = min(dfn[i], low[k]);
        }
        if (low[k] == dfn[k]) {
            int tmp;
            do {
                tmp = s.top();
                bh[tmp] = num;
                s.pop();
            } while (tmp != k);
            num++;
        }
    };
    for (int i = 0; i < n; i++) {
        if (bh[i] == -1) {
            ind = 1;
            dfs(i);
        }
    }
    vector<vector<int>> tiny(num);
    for (int i = 0; i < n; i++) {
        for (auto j : lj[i]) {
            if (bh[i] != bh[j]) {
                tiny[bh[i]].push_back(bh[j]); // multiple edge
            }
        }
    }
    return tiny;
}
