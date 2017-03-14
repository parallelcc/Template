// Copyright 2017 Parallelc 
#include <bits/stdc++.h>
using namespace std;  // NOLINT
vector<vector<pair<int, int>>> tarjan(const vector<vector<int>>& lj) {
    int n = lj.size();
    vector<int> dfn(n), low(n);
    int ind = 1;
    stack<pair<int, int>> s;
    vector<vector<pair<int, int>>> edge;
    function<void(int, int)> dfs = [&](int k, int pre) {
        dfn[k] = low[k] = ind++;
        for (auto i : lj[k]) {
            if (!dfn[i]) {
                s.emplace(k, i);
                dfs(i, k);
                low[k] = min(low[k], low[i]);
                // find it is cut
                if (dfn[k] <= low[i]) {
                    pair<int, int> tmp;
                    edge.resize(edge.size() + 1);
                    do {
                        tmp = s.top();
                        edge.back().push_back(move(s.top()));
                        s.pop();
                    } while (tmp.first != k || tmp.second != i);
                }
            } else if (i != pre) {
                low[k] = min(low[k], dfn[i]);
                // edge connect to ancestors
                if (dfn[k] > dfn[i])
                    s.emplace(k, i);
            }
        }
    };
    for (int i = 0; i < n; i++) {
        if (!dfn[i]) {
            ind = 1;
            dfs(i, i);
        }
    }
    return edge;
}
