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
bool equ(T a, T b, T c, T& x, T& y) {  // solutions of ax + by = c || ax = c (mod b)
    T d = exgcd(a, b, x, y);
    if (d == 0) return !c;  // a == b == 0
    if (c % d) return false;
    x *= c / d, y *= c / d;  // a solution
    a /= d, b /= d;  // all solution: x = x + b * t, y = y - a * t; loop of x % b is d
    T tx = x;
    x = (x % b + b) % b, y += (tx - x) / b * a;  // solution of min{Z*}
    return true;
}
