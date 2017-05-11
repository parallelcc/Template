#include <bits/stdc++.h>
using namespace std;
template <typename T> T gcd(T a, T b) { return b ? gcd(b, a % b) : a; }

template <typename T> T lcm(T a, T b) { return a * b / gcd(a, b); }
