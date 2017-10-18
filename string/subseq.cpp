#include <bits/stdc++.h>
using namespace std;

template <int N = 26>
struct SubSeq {
    vector<int> f[N];
    SubSeq(string& s) {
        int n = s.length();
        for (auto& i : f) i.resize(n + 1);
        vector<int> cur(N);
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            for (int j = cur[c]; j < i + 1; j++) f[c][j] = i + 1;
            cur[c] = i + 1;
        }
    }
    int get_result(string& s) {
        int cur = 0, n = s.length();
        for (int i = 0; i < n; i++) {
            cur = f[s[i] - 'a'][cur];
            if (cur == 0) return i;
        }
        return n;
    }
};
