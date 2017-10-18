// o(n)
#include <bits/stdc++.h>
using namespace std;

int get_min(const string& s) {
    int n = s.length();
    int i = 0, j = 1, k = 0;
    while(i < n && j < n && k < n) {
        int t = s[(i + k) % n] - s[(j + k) % n];
        if (t) {
            if (t > 0) i += k + 1;
            else j += k + 1;
            if (i == j) j++;
            k = 0;
        } else k++;
    }
    return min(i, j);
}
int get_max(const string& s) {
    int n = s.length();
    int i = 0, j = 1, k = 0;
    while(i < n && j < n && k < n) {
        int t = s[(i + k) % n] - s[(j + k) % n];
        if (t) {
            if (t > 0) j += k + 1;
            else i += k + 1;
            if (i == j) j++;
            k = 0;
        } else k++;
    }
    return min(i, j);
}
