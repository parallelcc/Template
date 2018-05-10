// Copyright 2017 Parallelc
#include <bits/stdc++.h>
#include <ext/numeric>
using namespace std;
using namespace __gnu_cxx;
template<typename T, class op = plus<T>, class sub = minus<T>>
class BIT {
 private:
     vector<T> tr;
     int lowbit(int x) {return x & (-x);}

 public:
     BIT() {}
     BIT(int n) {
         tr.resize(n + 1);
     }
     BIT(vector<T>& a) {
         int n = a.size();
         tr.resize(n + 1);
         for (int i = 0; i < n; i++) add(i, a[i]);
     }
     void add(int x, T k) {
         x++;
         for (int i = x; i < tr.size(); i += lowbit(i)) {
             tr[i] = op()(tr[i], k);
         }
     }
     T sum(int x) {
         T ans = identity_element(op());
         for (int i = x; i; i -= lowbit(i)) {
             ans = op()(ans, tr[i]);
         }
         return ans;
     }
     T que(int l, int r) {
         return sub()(sum(r), sum(l));
     }
};

struct node {
    int x, y, z, num, sum = 0;
    bool operator< (const node& e) const {
        if (x != e.x) return x < e.x;
        if (y != e.y) return y < e.y;
        return z < e.z;
    }
    bool operator== (const node& e) const {
        return x == e.x && y == e.y && z == e.z;
    }
};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<node> a(n), b(n);
    BIT<int> bit(k + 5);
    for (auto& i : a) cin >> i.x >> i.y >> i.z;
    sort(a.begin(), a.end());
    int cur = 0, f = 0;
    for (int i = 0; i < n; i++) {
        cur++;
        if (i == n - 1 || !(a[i] == a[i + 1])) {
            a[f] = a[i];
            a[f].num = f;
            a[f++].sum = cur;
            cur = 0;
        }
    }
    vector<int> ans(f);
    function<void(int, int)> cdq = [&](int l, int r) {
        if (l + 1 == r) return;
        int m = (l + r) / 2;
        cdq(l, m);
        cdq(m, r);
        int j = l, k = m;
        for (int i = l; i < r; i++) {
            if (j < m && (a[j].y <= a[k].y || k >= r)) {
                b[i] = a[j++];
                bit.add(b[i].z, b[i].sum);
            } else {
                b[i] = a[k++];
                ans[b[i].num] += bit.que(0, b[i].z + 1);
            }
        }
        for (int i = l; i < r; i++) {
            if (i < m) bit.add(a[i].z, -a[i].sum);
            a[i] = move(b[i]);
        }
    };
    cdq(0, f);
    vector<int> tmp(n);
    for (int i = 0; i < f; i++) tmp[ans[a[i].num] + a[i].sum - 1] += a[i].sum;
    for (int i = 0; i < n; i++) cout << tmp[i] << '\n';
    return 0;
}
