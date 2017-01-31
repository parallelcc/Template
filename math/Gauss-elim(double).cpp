// Copyright 2016 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
const double eps = 1e-9;
const int MAXN = 220;
double a[MAXN][MAXN], x[MAXN];
int equ, var;
int Gauss() {
    for (int k = 0, col = 0; k < equ && col < var; k++, col++) {
        int max_r = k;
        for (int i = k + 1; i < equ; i++) {
            if (fabs(a[i][col]) > fabs(a[max_r][col])) max_r = i;
        }
        if (fabs(a[max_r][col] < eps)) return 0;
        if (k != max_r) {
            for (int j = col; j < var; j++) swap(a[k][j], a[max_r][j]);
            swap(x[k], x[max_r]);
        }
        x[k] /= a[k][col];
        for (int j = col + 1; j < var; j++) a[k][j] /= a[k][col];
        a[k][col] = 1;
        for (int i = 0; i < equ; i++) {
            if (i != k) {
                x[i] -= x[k] * a[i][k];
                for (int j = col + 1; j < var; j++) {
                    a[i][j] -= a[k][j] * a[i][col];
                }
                a[i][col] = 0;
            }
        }
    }
    return 1;
}
