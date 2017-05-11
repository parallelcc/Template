// Copyright 2016 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
const double eps = 1e-9;
vector<double> Gauss(vector<vector<double>>& a, vector<double>& x) {
    int n = a.size();
    int m = a[0].size();
    vector<double> ans(m);
    vector<int> pos(n), free;
    int z = 0;
    for (int i = 0; i < m && z < n; i++, z++) {
        int r = z;
        for (int j = z + 1; j < n; j++) {
            if (abs(a[j][i]) - abs(a[r][i]) > eps) r = j;
        }
        if (abs(a[r][i]) <= eps) {
            free.push_back(i);
            z--;
            continue;
        }
        swap(a[z], a[r]);
        swap(x[z], x[r]);
        x[z] /= a[z][i];
        for (int j = i + 1; j < m; j++) a[z][j] /= a[z][i];
        a[z][i] = 1;
        for (int j = z + 1; j < n; j++) {
            if (abs(a[j][i]) > eps) {
                x[j] -= x[z] * a[j][i];
                for (int k = i + 1; k < m; k++) {
                    if (abs(a[z][k]) > eps) a[j][k] -= a[z][k] * a[j][i];
                }
                a[j][i] = 0;
            }
        }
        ans[i] = x[z];
        pos[z] = i;
    }
    for (int i = z; i < n; i++) if (abs(x[i]) > eps) return vector<double>();
    // TODO: enumerate free_x
    for (int i = z - 1; i >= 0; i--) {
        for (int j = pos[i] + 1; j < m; j++) {
            if (abs(a[i][j]) > eps) ans[pos[i]] -= a[i][j] * ans[j];
        }
    }
    return ans;
}

#include <tr2/dynamic_bitset>
using namespace tr2;
using db = dynamic_bitset<>;
template<size_t N, size_t M>
db Gauss(vector<db>& a) {
    int n = a.size();
    int m = a[0].size() - 1;
    db ans(m, 0);
    vector<int> pos(n), free;
    int z = 0;
    for (int i = 0; i < m && z < n; i++, z++) {
        int r = z;
        while (r < n - 1 && !a[r][i]) r++;
        if (!a[r][i]) {
            free.push_back(i);
            z--;
            continue;
        }
        swap(a[z], a[r]);
        for (int j = 0; j < n; j++) {
            if (j != z && a[j][i]) {
                a[j] ^= a[z];
            }
        }
        ans[i] = a[z][m];
        pos[z] = i;
    }
    for (int i = z; i < n; i++) if (a[i][m]) return db();
    // TODO: enumerate free_x
    /*
    for (int i = 0; i < n; i++) {
        for (auto& j : free) {
            if (a[i][j]) ans[pos[i]] = ans[pos[i]] ^ ans[j];
        }
    }
    */
    return ans;
}

using LL = int64_t;
using T = LL;
T exgcd(T a, T b, T& x, T& y) {  // a solution of ax + by = gcd(a, b)
    if (b == 0) return x = 1, y = 0, a;
    T d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
T inv(T a, T mod) {  // ax = 1(mod p)
    T x, y;
    T d = exgcd(a, mod, x, y);
    if (d == 1) return (x % mod + mod) % mod;
    else return -1;
}
template <typename T>
vector<T> Gauss(vector<vector<T>>& a, vector<T>& x, T mod) {  // two mods for check
    int n = a.size();
    int m = a[0].size();
    vector<T> ans(m);
    vector<int> pos(n), free;
    int z = 0;
    for (int i = 0; i < m && z < n; i++, z++) {
        int r = z;
        while (r < n - 1 && !a[r][i]) r++;
        if (!a[r][i]) { 
            free.push_back(i);
            z--; 
            continue; 
        } 
        swap(a[z], a[r]);
        swap(x[z], x[r]);
        T inv = ::inv(a[z][i], mod);
        if (inv == -1) return vector<T>();
        x[z] = x[z] * inv % mod;
        for (int j = i + 1; j < m; j++) a[z][j] = a[z][j] * inv % mod;
        a[z][i] = 1;
        for (int j = z + 1; j < n; j++) {
            if (a[j][i]) {
                x[j] = (x[j] - x[z] * a[j][i] % mod + mod) % mod;
                for (int k = i + 1; k < m; k++) {
                    if (a[z][k]) a[j][k] = (a[j][k] - a[z][k] * a[j][i] % mod + mod) % mod;
                }
                a[j][i] = 0;
            }
        }
        ans[i] = x[z];
        pos[z] = i;
    }
    for (int i = z; i < n; i++) if (x[i]) return vector<T>();
    // TODO: enumerate free_x
    for (int i = z - 1; i >= 0; i--) {
        for (int j = pos[i] + 1; j < m; j++) {
            if (a[i][j]) ans[pos[i]] = (ans[pos[i]] - a[i][j] * ans[j] % mod + mod) % mod;
        }
    }
    return ans;
}
