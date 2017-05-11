// Copyright 2016 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
int hungary(const vector<vector<int>>& lj, int m) {
    int n = lj.size();
    static vector<int> rlink, us;  //, llink;
    // llink.resize(n), fill(llink.begin(), llink.end(), -1);
    rlink.resize(m), fill(rlink.begin(), rlink.end(), -1);
    us.resize(m), fill(us.begin(), us.end(), -1);
    static function<bool(int, int)> dfs = [&](int k, int d) {  // make k link to right
        for (auto i : lj[k]) {
            if (us[i] != d) {
                us[i] = d;
                if (rlink[i] == -1|| dfs(rlink[i], d)) {
                    rlink[i] = k;  // make or change link
                    // llink[k] = i;
                    return true;
                }
            }
        }
        return false;
    };
    int num = 0;  // max linked egde number
    for (int i = 0; i < n; i++) {
        if (dfs(i, i)) {  // link successfully
            num++;
        }
    }
    return num;
}
