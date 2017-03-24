// h(x) <= h*(x)
// --h(x) - h(x + 1) <= g(x + 1) - g(x)
#include <bits/stdc++.h>
using namespace std;
using Status = int;
using T = int;
const T INF = 0x3f3f3f3f;
struct node {
    Status x;
    // value
    T f, g, h;
    bool operator<(const node &a) const { return f > a.f; }
    void update() {  // update f
        h = ;
        f = g + h;
    }
};
T Astar(Status S, Status N) {  // n nodes, from S to N
    unordered_set<Status> us;    // if in close or not
    unordered_map<Status, T> a;  // node's f in open or close
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
        } while (!q.empty() && us.find(now.x) != us.end());
        if (us.find(now.x) == us.end()) {
            us.insert(now.x);
            if (now.x == N)
                break;
            for () {
                node tmp;  // new node
                tmp.x = ;
                tmp.g = now.g + ;
                tmp.update();
                if (a.find(tmp.x) == a.end() || a[tmp.x] > tmp.f) {
                    a[tmp.x] = tmp.f;
                    q.push(tmp);
                    us.erase(tmp.x);
                }
            }
        }
    }
    if (us.find(N) != us.end()) return a[N];
    else return INF;
}
