// Copyright 2017 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
typedef int64_t LL;
const double PI = acos(-1);
void rader(vector<complex<double> >& y) {
    int len = y.size();
    int i, j, k;
    for (i = 1, j = len / 2; i < len - 1; i++) {
        if (i < j) swap(y[i], y[j]);
        k = len / 2;
        while (j >= k) {
            j -= k;
            k /= 2;
        }
        if (j < k) j += k;
    }
}
void fft(vector<complex<double> >& y, int on) {
    int len = y.size();
    rader(y);
    for (int h = 2; h <= len; h <<= 1) {
        complex<double> wn(cos(-on * 2 * PI / h), sin(-on * 2 * PI / h));
        for (int j = 0; j < len; j += h) {
            complex<double> w(1, 0);
            for (int k = j; k < j + h / 2; k++) {
                complex<double> u = y[k];
                complex<double> t = w * y[k + h / 2];
                y[k] = u + t;
                y[k + h / 2] = u - t;
                w = w * wn;
            }
        }
    }
    if (on == -1) for (int i = 0; i < len; i++) y[i].real(y[i].real() / len);
}
class BigInt {
 private:
     string num;
     string sign;

 public:
     const string to_string() const {
         if (this->sign == "-") return this->sign + this->num;
         else return this->num;
     }
     BigInt() {
         this->num = "0";
         this->sign = "+";
     }
     BigInt(const int& S) {
         if (S < 0) {
             this->num = std::to_string(-S);
             this->sign = "-";
         } else {
             this->num = std::to_string(S);
             this->sign = "+";
         }
     }
     BigInt(const LL& S) {
         if (S < 0) {
             this->num = std::to_string(-S);
             this->sign = "-";
         } else {
             this->num = std::to_string(S);
             this->sign = "+";
         }
     }
     BigInt(const string& S) {
         if (S[0] == '-') {
             this->num = S.substr(1);
             this->sign = "-";
         } else {
             this->num = S;
             this->sign = "+";
         }
         int flag = 0;
         while (flag < (int)this->num.length() - 1 && this->num[flag] == '0') flag++;
         this->num = this->num.substr(flag);
     }
     BigInt(const char* const& S) {
         new (this)BigInt(string(S));
     }
     BigInt(const BigInt& S) {
         this->num = S.num;
         this->sign = S.sign;
     }
     BigInt& operator= (const BigInt& S) {
         this->num = S.num;
         this->sign = S.sign;
         return *this;
     }
     bool operator< (const BigInt& S) const {
         if (this->sign != S.sign) {
             if (this->sign == "-") return true;
             else return false;
         } else {
             if (this->sign == "-") {
                 if (this->num.length() == S.num.length()) {
                     return this->num > S.num;
                 } else {
                     return this->num.length() > S.num.length();
                 }
             } else {
                 if (this->num.length() == S.num.length()) {
                     return this->num < S.num;
                 } else {
                     return this->num.length() < S.num.length();
                 }
             }
         }
     }
     bool operator> (const BigInt& S) const {
         return S < *this;
     }
     bool operator== (const BigInt& S) const {
         if (this->num == S.num && this->sign == S.sign) return true;
         else return false;
     }
     bool operator!= (const BigInt& S) const {
         return !(*this == S);
     }
     bool operator<= (const BigInt& S) const {
         return *this == S || *this < S;
     }
     bool operator>= (const BigInt& S) const {
         return *this == S || *this > S;
     }
     friend BigInt abs(const BigInt& S) {
         BigInt ans = S;
         if (ans.sign == "-") ans.sign = "+";
         return ans;
     }
     friend BigInt operator- (const BigInt& S) {
         BigInt ans = S;
         if (ans.sign == "-") ans.sign = "+";
         else ans.sign = "-";
         return ans;
     }
     friend istream& operator>> (istream& in, BigInt& S) {
         string s;
         cin >> s;
         S = s;
         return in;
     }
     friend ostream& operator<< (ostream& out, const BigInt& S) {
         cout << S.to_string();
         return out;
     }
     BigInt operator+ (const BigInt& S) const {
         BigInt ans, sub;
         if (this->num.length() < S.num.length()) {
             ans = S;
             sub = *this;
         } else if (this->num.length() == S.num.length()) {
             if (this->num < S.num) {
                 ans = S;
                 sub = *this;
             } else {
                 ans = *this;
                 sub = S;
             }
         } else {
             ans = *this;
             sub = S;
         }
         int sub_l = sub.num.length();
         int ans_l = ans.num.length();
         if (this->sign == S.sign) {
             for (int i = 1; i <= sub_l; i++) {
                 ans.num[ans_l - i] += sub.num[sub_l - i] - '0';
             }
             int flag = 0;
             for (int i = 1; i <= ans_l; i++) {
                 if (ans.num[ans_l - i] > '9') {
                     ans.num[ans_l - i] -= 10;
                     if (i == ans_l) {
                         flag = 1;
                     } else {
                         ans.num[ans_l - i - 1] += 1;
                     }
                 } else if (i >= sub_l) {
                     break;
                 }
             }
             if (flag) ans.num = "1" + ans.num;
         } else {
             for (int i = 1; i <= sub_l; i++) {
                 ans.num[ans_l - i] -= sub.num[sub_l - i] - '0';
             }
             for (int i = 1; i <= ans_l; i++) {
                 if (ans.num[ans_l - i] < '0') {
                     ans.num[ans_l - i] += 10;
                     ans.num[ans_l - i - 1] -= 1;
                 } else if (i >= sub_l) {
                     break;
                 }
             }
             int flag = 0;
             while (flag < ans_l - 1 && ans.num[flag] == '0') flag++;
             ans.num = ans.num.substr(flag);
             if (ans.num == "0") ans.sign = "+";
         }
         return ans;
     }
     BigInt operator- (const BigInt& S) const {
         BigInt sub = S;
         if (sub.sign == "+") sub.sign = "-";
         else sub.sign = "+";
         return *this + sub;
     }
     BigInt operator* (const BigInt& S) const {
         BigInt res;
         if (S.sign == this->sign) res.sign = "+";
         else res.sign = "-";
         vector<complex<double> > x1, x2;
         vector<int> sum;
         string str1 = this->num, str2 = S.num;
         int len1 = str1.length();
         int len2 = str2.length();
         int len = 1;
         while (len < len1 * 2 || len < len2 * 2) len <<= 1;
         for (int i = 0; i < len1; i++) {
             x1.push_back(complex<double>(str1[len1 - 1 - i] - '0', 0));
         }
         for (int i = len1; i < len; i++) {
             x1.push_back(complex<double>(0, 0));
         }
         for (int i = 0; i < len2; i++) {
             x2.push_back(complex<double>(str2[len2 - 1 -i] - '0', 0));
         }
         for (int i = len2; i < len; i++) {
             x2.push_back(complex<double>(0, 0));
         }
         fft(x1, 1);
         fft(x2, 1);
         for (int i = 0; i < len; i++) x1[i] = x1[i] * x2[i];
         fft(x1, -1);
         for (auto i : x1) sum.push_back((int)(i.real() + 0.5));
         for (int i = 0; i < len; i++) {
             sum[i + 1] += sum[i] / 10;
             sum[i] %= 10;
         }
         len = len1 + len2 - 1;
         while (sum[len] <= 0 && len > 0) len--;
         res.num = "";
         for (int i = len; i >= 0; i--) res.num += sum[i] + '0';
         if (res.num == "0") res.sign = "+";
         return res;
     }
     BigInt operator/ (const BigInt& S) const {
         if (S == 0) throw;
         BigInt res;
         if (S.sign == this->sign) res.sign = "+";
         else res.sign = "-";
         BigInt sub = abs(*this), ans = abs(S);
         int w = sub.num.length() - ans.num.length();
         for (int i = 0; i < w; i++) ans.num += "0";
         while (w >= 0) {
             int s = 0;
             while (ans <= sub) {
                 sub -= ans;
                 s++;
             }
             res.num += s + '0';
             ans.num = ans.num.substr(0, ans.num.length() - 1);
             w--;
         }
         int flag = 0;
         while (flag < (int)res.num.length() - 1 && res.num[flag] == '0') flag++;
         res.num = res.num.substr(flag);
         if (res.num == "0") res.sign = "+";
         return res;
     }
     BigInt operator% (const BigInt& S) const {
         if (S == 0) throw;
         BigInt sub = abs(*this), ans = abs(S);
         int w = sub.num.length() - ans.num.length();
         for (int i = 0; i < w; i++) ans.num += "0";
         while (w >= 0) {
             int s = 0;
             while (ans <= sub) {
                 sub -= ans;
                 s++;
             }
             w--;
             ans.num = ans.num.substr(0, ans.num.length() - 1);
         }
         sub.sign = this->sign;
         if (sub.num == "0") sub.sign = "+";
         return sub;
     }
     BigInt& operator+= (const BigInt& S) {
         return *this = *this + S;
     }
     BigInt& operator-= (const BigInt& S) {
         return *this = *this - S;
     }
     BigInt& operator*= (const BigInt& S) {
         return *this = *this * S;
     }
     BigInt& operator/= (const BigInt& S) {
         return *this = *this / S;
     }
     BigInt& operator%= (const BigInt& S) {
         return *this = *this % S;
     }
     BigInt subnum(int r, int l) {
         BigInt ans = this->num.substr(this->num.length() - l, l - r);
         ans.sign = this->sign;
         return ans;
     }
     BigInt subnum(int l) {
         return this->subnum(0, l);
     }
};
