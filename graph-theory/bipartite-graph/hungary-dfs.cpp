// Copyright 2016 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
const int N = 1005;  // left max
const int M = 1005;  // right max
vector<int> lj[N];  // from left to right
int n, m;  // left, right num
class hungary {
 private:
    int llink[N], rlink[M];  // left link to right, right link to left
    int used[M];  // record used right point in a dfs
    int d;  // current root
    bool dfs(int k) {  // find a method that can make k link to right
        for (int i = 0; i < lj[k].size(); i++) {
            if (used[lj[k][i]] != d) {
                used[lj[k][i]] = d;
                if (rlink[lj[k][i]] == -1 || dfs(rlink[lj[k][i]])) {
                    rlink[lj[k][i]] = k;  // make or change link
                    llink[k] = lj[k][i];
                    return true;
                }
            }
        }
        return false;
    }

 public:
    int get_result() {
        int link_edge_num = 0;  // max linked egde number
        for (d = 1; d <= n; d++) if (dfs(d)) {  // link successfully
            link_edge_num++;
        }
        return link_edge_num;
    }
    hungary() {
        fill(rlink, rlink + m + 1, -1);
        fill(llink, llink + n + 1, -1);
        fill(used, used + m + 1, -1);
    }
    ~hungary() {}
};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int k;  // edge num
    while (cin >> k >> n >> m) {
        for (int i = 0; i <= n; i++) lj[i].clear();
        for (int i = 0; i < k; i++) {
            int u, v;
            cin >> u >> v;
            lj[u].push_back(v);
        }
        hungary *a = new hungary();
        cout << a->get_result() << '\n';
        delete a;
    }
}
