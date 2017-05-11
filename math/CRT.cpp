#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;
using T = LL;
T exgcd(T a, T b, T& x, T& y) {  // a solution of ax + by = gcd(a, b)
    if (b == 0) return x = 1, y = 0, a;
    T d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
pair<T, T> CRT(T mf, T af, T ms, T as) {
    T x, y;
    T g = exgcd(mf, ms, x, y);  // x is the inv of mf mod ms
    if ((as - af) % g) return {-1, -1};
    T m = ms / g;
    T a = af + ((as - af) / g * x % m + m) % m * mf;
    m *= mf;
    return {m, a};
}
