#include <bits/stdc++.h>
using namespace std;

int LIS(vector<int>& a) {
    vector<int> b;
    b.reserve(a.size());
    for (auto i : a) {
        auto it = lower_bound(a.begin(), a.end(), i);  // upper: not decrease
        if (it != a.end()) *it = i;
        else b.push_back(i);
    }
    return b.size();
}
