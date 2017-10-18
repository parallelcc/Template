#include <bits/stdc++.h>
using namespace std;
using T = int;
vector<T> LSH(vector<T>& a) {
    auto lsh = a;
    sort(lsh.begin(), lsh.end());
    lsh.erase(unique(lsh.begin(), lsh.end()), lsh.end());
    for (auto& i : a) {
        i = lower_bound(lsh.begin(), lsh.end(), i) - lsh.begin();
    }
    return lsh;
}
