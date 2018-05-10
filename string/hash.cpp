#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;
using ULL = uint64_t;
const LL mod = 999999937;
ULL base = 31;
vector<ULL> x;
void init(int n) {
    x.resize(n);
    x[0] = 1;
    for (int i = 1; i < n; i++) { x[i] = x[i - 1] * base; }
}
struct StrHash {
    char a = 'a';
    vector<ULL> h{0};
    string s;
    StrHash(int n) { h.reserve(n); }
    StrHash(string&& t) {
        s = t;
        h.resize(s.length() + 1);
        for (int i = 1; i < h.size(); i++) {
            h[i] = h[i - 1] * base + s[i - 1] - a + 1;
        }
    }
    void push_back(char c) { s += c; h.push_back(h.back() * base + c - a + 1); }
    void pop_back() { 
        if (s == "") return;
        s.pop_back(); 
        h.pop_back(); 
    }
    ULL substr(int l, int r) const { return h[r] - h[l] * x[r - l]; }  // [, )  // !!! + mod
};
int lcp(const StrHash& a, int al, int ar, const StrHash& b, int bl, int br) {
    auto check = [&](int k) {
        return a.substr(al, al + k) == b.substr(bl, bl + k);
    };
    int l = 0, r = min(ar - al, br - bl) + 1;
    while (l < r) {
        int mid = (l + r) / 2;
        if (check(mid)) l = mid + 1;
        else r = mid;
    }
    return r - 1;
}
int cmp(const StrHash& a, int al, int ar, const StrHash& b, int bl, int br) {
    int r = lcp(a, al, ar, b, bl, br);
    if (r == min(ar - al, br - bl)) {
        if (ar - al < br - bl) return -1;
        else if (ar - al > br - bl) return 1;
        else return 0;
    } else {
        if (a.s[al + r] < b.s[bl + r]) return -1;
        else return 1;
    }
}
bool operator<(const StrHash& s, const StrHash& t) {
    return cmp(s, 0, s.s.length(), t, 0, t.s.length()) == -1;
}
