#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;
template<typename T>
class Part_Blocks {
    int k;
    vector<T> a, tag, sum;

 public:
    Part_Blocks(vector<T>&& b) : a(b) {
        int n = a.size();
        k = sqrt(n);
        int m = n / k;
        if (m * k != n) m++;
        tag.resize(m); sum.resize(m);
        for (int i = 0; i < m; i++) {
            for (int j = anum(i); j < anum(i + 1); j++) {
                sum[i] += a[j];
            }
        }
    }
    inline int anum(int v) { return min<int>(v * k, a.size()); }
    inline int bnum(int v) { return v / k; }
    void aupd(int l, int r, T v) {
        int b = bnum(l);
        for (int i = l; i < r; i++) a[i] += v, sum[b] += v;
    }
    void bupd(int l, int r, T v) {
        for (int i = l; i < r; i++) tag[i] += v;
    }
    void upd(int l, int r, T v) {
        int L = bnum(l), R = bnum(r - 1);
        if (L == R) aupd(l, r, v);
        else { aupd(l, anum(L + 1), v), bupd(L + 1, R, v), aupd(anum(R), r, v); }
    }
    T aque(int l, int r) {
        int b = bnum(l); T ans = 0;
        for (int i = l; i < r; i++) ans += a[i] + tag[b];
        return ans;
    }
    T bque(int l, int r) {
        T ans = 0; 
        for (int i = l; i < r; i++) ans += sum[i] + tag[i] * k;
        return ans;
    }
    T que(int l, int r) {
        int L = bnum(l), R = bnum(r - 1);
        if (L == R) return aque(l, r);
        else { return aque(l, anum(L + 1)) + bque(L + 1, R) + aque(anum(R), r); }
    }
};
