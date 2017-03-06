// Copyright 2017 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
template <typename T>
class Mat {
 public:
     int n, m;
     vector<vector<T> > val;
     Mat(const int n, const int m) : n(n), m(m) {
        val.resize(n);
        for (auto& i : val) {
            i.resize(m);
        }
     }
     explicit Mat(const int n) : Mat(n, n) {}
     friend istream& operator>> (istream& in, Mat& t) {
         for (auto& i : t.val) {
             for (auto& j : i) in >> j;
         }
         return in;
     }
     friend ostream& operator<< (ostream& out, const Mat& t) {
         for (auto& i : t.val) {
             for (int j = 0; j < t.m; j++) {
                 out << i[j];
                 if (j == t.m - 1) out << endl;
                 else out << " ";
             }
         }
         return out;
     }
     friend const Mat operator- (const Mat& t) {
         auto ans = t;
         for (auto& i : ans.val) {
             for (auto& j : i) {
                 j = -j;
             }
         }
         return ans;
     }
     friend const Mat operator+ (const Mat& t, const Mat& s) {
         if (t.n != s.n || t.m != s.m) throw;
         auto ans = t;
         for (int i = 0; i < ans.n; i++) {
             for (int j = 0; j < ans.m; j++) {
                ans.val[i][j] += s.val[i][j];
             }
         }
         return ans;
     }
     friend const Mat operator- (const Mat& t, const Mat& s) {
         return t + (-s);
     }
     friend const Mat operator* (const Mat& t, const Mat& s) {
         if (t.m != s.n) throw;
         Mat ans(t.n, s.m);
         for (int i = 0; i < ans.n; i++) {
             for (int j = 0; j < ans.m; j++) {
                 ans.val[i][j] = T(0);
                 for (int k = 0; k < t.m; k++) {
                     ans.val[i][j] += t.val[i][k] * s.val[k][j];  // % mod;
                     // ans.val[i][j] %= mod;
                 }
             }
         }
         return ans;
     }
     template <typename S>
     friend const Mat operator* (const Mat& t, const S& s) {
        auto ans = t;
        for (auto& i : ans.val) {
            for (auto& j : i) {
                j *= s;
            }
        }
        return ans;
     }
     template <typename S>
     friend const Mat operator/ (const Mat& t, const S& s) {
         auto ans = t;
         for (auto& i : ans.val) {
             for (auto& j : i) {
                 j /= s;
             }
         }
         return ans;
     }
     template <typename S>
     friend const Mat operator% (const Mat& t, const S& s) {
         auto ans = t;
         for (auto& i : ans.val) {
             for (auto& j : i) {
                 j %= s;
             }
         }
         return ans;
     }
     template <typename S>
     friend const Mat operator* (const S& s, const Mat& t) {
         return t * s;
     }
     int Gauss(vector<T>& x) {
         int z = 0;
         auto ans = *this;
         for (int i = 0, j = 0; i < ans.m && j < ans.n; i++, j++) {
             int r = j;
             // if float, need fabs && eps
             for (int k = j + 1; k < ans.n; k++) {
                 if (abs(ans.val[k][i]) > abs(ans.val[r][i])) r = k;
             }
             if (ans.val[r][i] == T(0)) {
                 j--;
                 continue;
             } else {
                 z++;
             }
             swap(ans.val[j], ans.val[r]);
             swap(x[j], x[r]);
             /*
             for (int k = 0; k < ans.n; k++) {
                 if (k != j && ans.val[k][i]) {
                     x[k] ^= x[j];
                     for (int l = i; l < ans.m; l++) {
                         ans.val[k][l] ^= ans.val[j][l];
                     }
                 }
             }
             */
             x[j] /= ans.val[j][i];
             for (int k = i + 1; k < ans.m; k++) ans.val[j][k] /= ans.val[j][i];
             ans.val[j][i] = T(1);
             for (int k = 0; k < ans.n; k++) {
                 if (k != j) {
                     x[k] -= x[j] * ans.val[k][i];
                     for (int l = i + 1; l < ans.m; l++) {
                         ans.val[k][l] -= ans.val[j][l] * ans.val[k][i];
                     }
                     ans.val[k][i] = T(0);
                 }
             }
         }
         for (int i = z; i < ans.n; i++) if (x[i] != T(0)) return -1;
         return z;
     }
};
