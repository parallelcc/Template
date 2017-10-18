#include <bits/stdc++.h>
using namespace std;
#include <tr2/dynamic_bitset>
using namespace tr2;
using db = dynamic_bitset<>;
int sh_or1(string& s, string& t) {
    int n = s.length();
    int m = t.length();
    static vector<db> b(26);
    for (auto& i : b) i.set(), i.resize(m, 1);
    for (int i = 0; i < n; i++) b[t[i] - 'a'].reset(i);
    static db d;
    d.resize(m);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        (d <<= 1) |= b[s[i] - '0'];
        if (i >= m - 1 && !d[m - 1]) ans++;
    }
    return ans;
}
int sh_or2(string& s, string& t) {
    int n = s.length();
    int m = t.length();
    static vector<db> b(26);
    for (auto& i : b) i.set(), i.resize(n, 1);
    for (int i = 0; i < n; i++) b[s[i] - 'a'].reset(i);
    static db d;
    d.reset();
    d.resize(n);
    for (int i = 0; i < m; i++) (d <<= 1) |= b[t[i] - '0'];
    int ans = 0;
    for (int i = m - 1; i < n; i++) if (!d[i]) ans++;
    return ans;
}
