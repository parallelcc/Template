#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;
using LD = long double;

using Permute = vector<int>;
const int N = 30;
vector<Permute> Base = {
    {9,10,11,3,4,5,6,7,8,0,1,2,12,13,14,15,16,17,20,19,18,29,22,23,24,25,26,27,28,21},
    {2,5,8,1,4,7,0,3,6,15,12,9,16,13,10,17,14,11,21,22,23,24,25,26,27,28,29,18,19,20},
    {9,10,11,12,13,14,15,16,17,0,1,2,3,4,5,6,7,8,20,19,18,29,28,27,26,25,24,23,22,21}
};
set<Permute> tb;
void dfs(const Permute& now) {
    tb.insert(now);
    Permute tmp(N);
    for (auto& i : Base) {
        for (int j = 0; j < N; j++) {
            tmp[j] = now[i[j]];
        }
        if (tb.find(tmp) != tb.end()) continue;
        dfs(tmp);
    }
}
int circle_num(const Permute& now) {
    int num = 0;
    vector<int> us(N);
    for (int i = 0; i < N; i++) {
        if (!us[i]) {
            int tmp = i;
            while (!us[tmp]) {
                us[tmp] = 1;
                tmp = now[tmp];
            }
            num++;
        }
    }
    return num;
}
vector<int> init() {
    vector<int> cn(N);
    iota(cn.begin(), cn.end(), 0);
    dfs(cn);
    cn.resize(tb.size());
    int k = 0;
    for (auto& i : tb) {
        /*
        cout << "{";
        for (int j = 0; j < N; j++) cout << i[j] << ",}"[j == N - 1];
        cout << '\n';
        */
        cn[k++] = circle_num(i);
    }
    return cn;
}
