// Copyright 2017 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
vector<int> tarjan(const vector<vector<int>>& lj) {
    int n = lj.size();
    vector<int> dfn(n), low(n), bh(n);
    int ind = 1, num = 1;
    stack<int> s;
    function<void(int, int)> dfs = [&](int k, int pre) {
        dfn[k] = low[k] = ind++;
        for (auto i : lj[k]) {
            if (!dfn[i]) {
                s.push(i);
                dfs(i, k);
                low[k] = min(low[k], low[i]);
                // bridge
                if (low[i] > dfn[k]) {
                    int tmp;
                    do {
                        tmp = s.top();
                        bh[tmp] = num;
                        s.pop();
                    } while (tmp != i);
                    num++;
                }
            } else if (i != pre)
                low[k] = min(low[k], dfn[i]);
        }
    };
    for (int i = 0; i < n; i++) {
        if (!dfn[i]) {
            ind = 1;
            dfs(i, i);
        }
    }
    while (!s.empty()) {
        bh[s.top()] = num;
        s.pop();
    }
    return bh;
}
