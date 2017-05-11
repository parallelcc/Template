// Copyright 2017 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
template <typename T>
class Mat {
 public:
     int n, m;
     vector<vector<T>> val;
     Mat(int n, int m) : n(n), m(m) {
        val.resize(n);
        for (auto& i : val) {
            i.resize(m);
        }
     }
     explicit Mat(int n) : Mat(n, n) {}
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
};
