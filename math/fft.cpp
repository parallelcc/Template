#include <bits/stdc++.h>
using namespace std;
using LD = long double;
const LD PI = acos(-1);
const double eps = 0.5;
namespace FFT {
    using CLD = complex<LD>;
    void rader(vector<CLD>& y) {
        int len = y.size();
        for (int i = 1, j = len / 2; i < len - 1; i++) {
            if (i < j) swap(y[i], y[j]);
            int k = len / 2;
            while (j >= k) {
                j -= k;
                k /= 2;
            }
            if (j < k) j += k;
        }
    }
    void DFT(vector<CLD>& y, int on) {
        int len = y.size();
        rader(y);
        for (int h = 2; h <= len; h <<= 1) {
            CLD wn(cos(-on * 2 * PI / h), sin(-on * 2 * PI / h));
            for (int j = 0; j < len; j += h) {
                CLD w(1, 0);
                for (int k = j; k < j + h / 2; k++) {
                    CLD u = y[k];
                    CLD t = w * y[k + h / 2];
                    y[k] = u + t;
                    y[k + h / 2] = u - t;
                    w = w * wn;
                }
            }
        }
        if (on == -1) for (auto& i : y) i.real(i.real() / len);
    }
    void conv(vector<CLD>& a, vector<CLD>& b) {
        int n = 1, m = a.size() + b.size() - 1;
        while (n < m) n <<= 1;
        a.resize(n), b.resize(n);
        DFT(a, 1);
        DFT(b, 1);
        for (int i = 0; i < n; i++) a[i] *= b[i];
        DFT(a, -1);
        a.resize(m);
    }
    void conv2(vector<CLD>& a, vector<CLD>& b) {
        int n = max(a.size(), b.size());
        a.resize(n), b.resize(n);
        reverse(b.begin(), b.end());
        conv(a, b);
        for (int i = 0; i < n - 1; i++) a[i] += a[i + n];
        a.resize(n);
        reverse(a.begin(), a.end());
    }
    vector<CLD> pinv(vector<CLD>& a, size_t n) {  // ax = 1 (mod x ^ n)
        if (n == 1) return vector<CLD>{(LD)1.0 / a[0]};
        else {
            auto b = pinv(a, (n + 1) >> 1);
            int len = 1;
            while (len < n << 1) len <<= 1;
            b.resize(len);
            vector<CLD> tmp(len);
            copy_n(a.begin(), min(n, a.size()), tmp.begin());
            DFT(b, 1);
            DFT(tmp, 1);
            for (int i = 0; i < len; i++) b[i] *= (LD)2.0 - tmp[i] * b[i];
            DFT(b, -1);
            b.resize(n);
            return b;
        }
    }
    void div(vector<CLD>& a, vector<CLD>& b) {
        if (a.size() < b.size()) {
            b = move(a);
            return;
        }
        int n = a.size() - b.size() + 1;
        int m = b.size();
        vector<CLD> c(a.rbegin(), a.rbegin() + n), d(b.rbegin(), b.rend());
        d = pinv(d, n);
        conv(c, d);
        c.resize(n);
        reverse(c.begin(), c.end());
        conv(b, c);
        b.resize(m);
        for (int i = 0; i < m; i++) b[i] = a[i] - b[i];
        DFT(c, -1);
        c.resize(n);
        a = move(c);
    }
}
