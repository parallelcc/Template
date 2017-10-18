#include <bits/stdc++.h>
using namespace std;
vector<int> in, out;
template <typename T>
vector<T> dfsx(vector<vector<int>>& lj, int r, vector<T>& dq) {
    int n = lj.size();
    in.resize(n), out.resize(n);
    vector<T> ans;
    ans.reserve(2 * n);
    function<void(int, int)> dfs = [&](int k, int pre) {
        in[k] = ans.size(); // [
        ans.push_back(dq[k]);
        for (auto i : lj[k]) {
            if (i == pre) continue;
            dfs(i, k);
        }
        out[k] = ans.size();  // )
        // ans.push_back(-dq[k]);  // ], sum of [0, in[k]] == sum from root to k
    };
    dfs(r, r);
    return ans;
}
