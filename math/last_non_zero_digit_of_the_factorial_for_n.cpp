#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;
using LD = long double;
const LL INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;

LL num_of_divisor(LL n, LL x) {
    LL tmp = x, ans = 0;
    while (tmp <= n) {
        ans += n / tmp;
        tmp *= x;
    }
    return ans;
}
int last_non_zero_digit_of_the_factorial_for(LL n) {
    LL two = num_of_divisor(n, 2);
    LL five = num_of_divisor(n, 5);
    // if (two && five) return 0;  // last_digit
    // if (five > two) return 5;  // be used for (n! / m!)
    LL three = 0, seven = 0, nine = 0;
    for (LL i = n; i > 0; i /= 2) {
        for (LL j = i; j > 0; j /= 5) {
            LL x = j / 10, y = j % 10;
            three += x + (y >= 3);
            seven += x + (y >= 7);
            nine += x + (y >= 9);
        }
    }
    int cir2[] = {6, 2, 4, 8};  // !!! 2^0 == 1
    int cir3[] = {1, 3, 9, 7};
    int cir7[] = {1, 7, 9, 3};
    int cir9[] = {1, 9, 1, 9};
    int ans = 1;
    if (two > five) ans *= cir2[(two - five) % 4];
    ans *= cir3[three % 4];
    ans *= cir7[seven % 4];
    ans *= cir9[nine % 4];
    return ans % 10;
}
