#include <bits/stdc++.h>
using namespace std;
vector<int> topsort(vector<vector<int>>& lj, vector<int>& rd) {  // !!! & rd
    int n = rd.size();
    stack<int, vector<int>> s;
    for (int i = 0; i < n; i++) {
        if (rd[i] == 0) s.push(i);
    }
    vector<int> ans;
    ans.reserve(n);
    while (!s.empty()) {
        // if (s.size() != 1)  // not only one answer
        int k = s.top();
        s.pop();
        ans.push_back(k);
        for (auto i : lj[k]) {
            rd[i]--;
            if (rd[i] == 0) s.push(i);
        }
    }
    if (ans.size() != n) return {};  // fail
    return ans;
}
