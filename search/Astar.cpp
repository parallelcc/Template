// h(x) <= h*(x)
#include <bits/stdc++.h>
using namespace std;
using Status = int;
using T = int;
const T INF = 0x3f3f3f3f;
unordered_map<Status, T> h;
struct node {
    Status x;
    // value
    T f, g;
    bool operator< (const node &a) const { return f > a.f; }
    void update() {  // update f
        if (h.find(x) == h.end()) h[x] = ;
        f = g + h[x];
    }
};
// ???
// Status encode() { return hash ??? }
// void decode(Status) { get ??? by Status }
T Astar(Status S, Status N) {  // n status, from S to N
    unordered_map<Status, T> a;  // status's f
    // start
    node now;  // current node
    now.x = S;
    now.g = 0;
    now.update();
    a[now.x] = now.f;
    priority_queue<node> q;
    q.push(now);
    while (!q.empty()) {
        do {
            now = q.top();
            q.pop();
        } while (now.f > a[now.x] && !q.empty());
        if (now.x == N) break;
        if (now.f == a[now.x]) {
            // decode(now.x);
            for () {
                // change ???
                node tmp;  // new node
                tmp.x = ;  // encode();
                tmp.g = now.g + ;
                tmp.update();
                if (a.find(tmp.x) == a.end() || a[tmp.x] > tmp.f) {
                    a[tmp.x] = tmp.f;
                    q.push(tmp);
                }
                // restore ???
            }
        }
    }
    if (a.find(N) != a.end()) return a[N];
    else return INF;
}
