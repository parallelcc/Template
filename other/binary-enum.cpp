#include <bits/stdc++.h>
using namespace std;

int main() {
    // enum subsets of s
    for (int i = s; i; i = (i - 1) & s) {
        // TODO
    }

    // enum subsets of ((1 << n) - 1) whose size is r
    for (int s = (1 << r) - 1; s < (1 << n);) {
        // TODO

        // next bigger number whose numbers of 1 is r
        int x = s & -s;
        int y = s + x;
        s = ((s & ~y) / x >> 1) | y;
    }
}
