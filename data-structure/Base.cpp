#include <bits/stdc++.h>
using namespace std;

// !!! 0
template <typename T>
struct LnBase {
    int sz, szc;
    vector<T> x;
    vector<int> y;
    LnBase() { sz = sizeof(T) << 3; szc = -1; x.resize(sz); y.resize(sz); }
    void clear() { szc = -1; fill(x.begin(), x.end(), 0); };
    T operator[](int h) const { return x[h]; }
    LnBase<T> operator+(const LnBase<T>& e) const {
        LnBase<T> tmp = *this;
        for (int i = 0; i < sz; i++) tmp.insert(e[i]);
        return tmp;
    }
    LnBase<T>& operator+=(const LnBase<T>& e) {
        for (int i = 0; i < sz; i++) insert(e[i]);
        return *this;
    }
    int insert(T v) {
        for (int i = sz - 1; i >= 0; i--) {
            if (v >> i & 1) {
                if (!x[i]) { x[i] = v; szc = -1; return i; }
                v ^= x[i];
            }
        }
        return -1;
    }
    int find(T v) {
        for (int i = sz - 1; i >= 0; i--) {
            if (v >> i & 1 && x[i]) v ^= x[i];
            if (!v) return 1;
        }
        return 0;
    }
    T Max(T s = 0) {
        for (int i = sz - 1; i >= 0; i--) { s = max(s, s ^ x[i]); }
        return s;
    }
    T Min() {
        for (int i = 0; i < sz; i++) if (x[i]) return x[i];
        return 0;
    }
    T Min(T s) {
        for (int i = sz - 1; i >= 0; i--) { s = min(s, s ^ x[i]); }
        return s;
    }
    void Canonicity() {
        for (int i = sz - 1; i > 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                if (x[i] >> j & 1) x[i] ^= x[j];
            }
        }
        szc = 0;
        for (int i = 0; i < sz; i++) if (x[i]) y[szc++] = i;
    }
    T Kth(T K) { // <, from 1
        if (szc < 0) Canonicity();
        if (K >= (T)1 << szc) return -1;
        T s = 0;
        for (int i = szc - 1; i >= 0; i--) if (K >> i & 1) s ^= x[y[i]];
        return s;
    }
};
