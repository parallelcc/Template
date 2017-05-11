#include <bits/stdc++.h>
using namespace std;
vector<int> tsat(vector<vector<int>>& lj, vector<pair<int, int>>& p) {
    int n = lj.size();
    int num = 0;
    auto tarjan = [&](const vector<vector<int>> &lj) {
        int n = lj.size();
        vector<int> dfn(n), low(n), bh(n, -1);
        int ind = 1;
        stack<int> s;
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
        return bh;
    };
    auto bh = tarjan(lj);
    vector<int> fx(n);
    for (auto& i : p) {
        if (bh[i.first] == bh[i.second]) return vector<int>();
        fx[bh[i.first]] = bh[i.second];
        fx[bh[i.second]] = bh[i.first];
    }
    vector<int> deg(num);
    vector<vector<int>> dag(num);
    for (int i = 0; i < n; i++) {
        for (auto j : lj[i]) {
            if (bh[i] != bh[j]) {
                dag[bh[j]].push_back(bh[i]);
                deg[bh[i]]++;
            }
        }
    }
    stack<int> s;
    for (int i = 0; i < num; i++) {
        if (!deg[i]) s.push(i);
    }
    vector<int> us(num);
    while (!s.empty()) {
        int k = s.top();
        s.pop();
        if (us[k] == 0) {
            us[k] = 1;
            us[fx[k]] = -1;
        }
        for (auto i : dag[k]) {
            if (!--deg[i]) s.push(i);
        }
    }
    vector<int> ans;
    ans.reserve(n >> 1);
    for (int i = 0; i < n; i++) {
        if (us[bh[i]] == 1) ans.push_back(i);
    }
    return ans;
}
