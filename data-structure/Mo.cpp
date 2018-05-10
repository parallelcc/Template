#include <bits/stdc++.h>
using namespace std;
int main() {
    struct Q {
        int l, r, id, block;  // [,)
    };
    int q;
    cin >> q;
    vector<Q> que(q);
    for (int i = 0; i < q; i++) {
        cin >> que[i].l >> que[i].r;
        que[i].id = i;
    }
    int v = sqrt(q);
    for (auto& i : que) i.block = i.l / v;
    sort(que.begin(), que.end(), [&](const Q& s, const Q& e) {
        if (s.block == e.block) return s.r < e.r;
        return s.l < e.l;
    });
    vector<T> ans(q);
    int l = que[0].l, r = que[0].l;
    for (auto& i : que) {
        for (; r < i.r; r++) upd(r, 1);
        for (; r > i.r; r--) upd(r - 1, -1);
        for (; l < i.l; l++) upd(l, -1);
        for (; l > i.l; l--) upd(l - 1, 1);
        ans[i.id] = ;
    }
}
