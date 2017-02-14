// Copyright 2017 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
template <typename T>
class Frac {
 private:
     void simply() {
         T g = __gcd(num, den);
         num /= g;
         den /= g;
         if (den < T(0)) {
             den = -den;
             num = -num;
         }
     }

 public:
     T num, den;
     Frac(const T& t, const T& s = 1) {
         num = t;
         den = s;
         simply();
     }
     Frac() : Frac(0, 1) {}
     double to_double() const {
         return (double)num / den;
     }
     friend Frac<T> operator- (const Frac<T>& t) {
         auto ans = t;
         ans.num = -ans.num;
         return ans;
     }
     friend Frac<T> abs(const Frac<T>& t) {
         auto ans = t;
         if (ans.num < T(0)) ans.num = -ans.num;
         return ans;
     }
     friend ostream& operator<< (ostream& out, const Frac<T>& t) {
         out << t.num << "/" << t.den;
         return out;
     }
     friend Frac<T> operator+ (const Frac<T>& t, const Frac<T>& s) {
         auto ans = t;
         ans.num = ans.num * s.den + s.num * ans.den;
         ans.den *= s.den;
         ans.simply();
         return ans;
     }
     friend Frac<T> operator- (const Frac<T>& t, const Frac<T>& s) {
         return t + (-s);
     }
     friend Frac<T> operator* (const Frac<T>& t, const Frac<T>& s) {
         auto ans = t;
         ans.num *= s.num;
         ans.den *= s.den;
         ans.simply();
         return ans;
     }
     friend Frac<T> operator/ (const Frac<T>& t, const Frac<T>& s) {
         if (s == T(0)) throw;
         auto ans = s;
         swap(ans.num, ans.den);
         return t * ans;
     }
     friend Frac<T>& operator+= (Frac<T>& t, const Frac<T>& s) {
         return t = t + s;
     }
     friend Frac<T>& operator-= (Frac<T>& t, const Frac<T>& s) {
         return t = t - s;
     }
     friend Frac<T>& operator*= (Frac<T>& t, const Frac<T>& s) {
         return t = t * s;
     }
     friend Frac<T>& operator/= (Frac<T>& t, const Frac<T>& s) {
         return t = t / s;
     }
     friend bool operator< (const Frac<T>& t, const Frac<T>& s) {
         return t.num * s.den < s.num * t.den;
     }
     friend bool operator> (const Frac<T>& t, const Frac<T>& s) {
         return s < t;
     }
     friend bool operator== (const Frac<T>& t, const Frac<T>& s) {
         return t.num == s.num && t.den == s.den;
     }
     friend bool operator!= (const Frac<T>& t, const Frac<T>& s) {
         return !(t == s);
     }
     friend bool operator<= (const Frac<T>& t, const Frac<T>& s) {
         return t < s || t == s;
     }
     friend bool operator>= (const Frac<T>& t, const Frac<T>& s) {
         return t > s || t == s;
     }
};
