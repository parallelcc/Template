#include <bits/stdc++.h>
using namespace std;
using uint = uint64_t;
uint xor_n(uint n) {
    uint t = n & 3;
    if (t & 1) return t / 2u ^ 1;
    return t / 2u ^ n;
}
