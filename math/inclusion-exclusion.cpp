#include <bits/stdc++.h>
using namespace std;

template <typename T>
vector<T> inc_exc(vector<T>& a) {
    vector<T> b;
    b.push_back(-1);
    for (auto& i : a) {
        int m = b.size();
        for (int j = 0; j < m; j++) b.push_back(- i * b[j]);
    }
    return b;
}
