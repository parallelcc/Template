#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;
using LD = long double;
const LL INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;

template <typename T>
LL Cantor(const vector<T>& a) {  // ans from 0
    int n = a.size();
    LL ans = 0, fac = 1;
    for (int i = 2; i < n; i++) fac *= i;
    for (int i = 0; i < n; i++) {
        int num = 0;
        for (int j = i + 1; j < n; j++) if (a[j] < a[i]) num++;
        ans += fac * num;
        if (i != n - 1) fac /= n - i - 1;
    }
    return ans;
}

template <typename T>
vector<T> deCantor(const vector<T>& a, LL k) {  // a is sorted, k from 0
    int n = a.size();
    vector<T> ans(n);
    vector<int> us(n);
    LL fac = 1;
    for (int i = 2; i < n; i++) fac *= i;
    for (int i = 0; i < n; i++) {
        LL t = k / fac;
        int now = 0;
        while (us[now]) now++;
        while (t--) {
            now++;
            while (us[now]) now++;
        }
        ans[i] = a[now];
        us[now] = 1;
        k %= fac;
        if (i != n - 1) fac /= n - i - 1;
    }
    return ans;
}
