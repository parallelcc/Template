#include <bits/stdc++.h>
#include <ext/rope>
using namespace __gnu_cxx;
using namespace std;
vector<rope<int>> bcj;
inline int gr(int i, int x) {
    int z = bcj[i][x];
    if (z == x) return x;
    int f = gr(i, z);
    if (f != z) bcj[i].replace(x, f);
    return f;
}
inline void mg(int i, int x, int y) {
    x = gr(i, x), y = gr(i, y);
    if (x ^ y) bcj[i].replace(y, x);
}
