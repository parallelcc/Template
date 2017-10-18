#include<bits/stdc++.h>
using namespace std;
template<typename T, class op = less<T>>
class monque {
 private:
     deque<pair<T, int>> d;
     int l = 0, t = 0;

 public:
     bool empty() {
         return l == t;
     }
     size_t size() {
         return t - l;
     }
     void push(const T& k) {
        while (!d.empty() && !op()(d.back().first, k)) d.pop_back();
        d.emplace_back(k, t++);
     }
     void pop() {
         if (empty()) return;
         l++;
         if (l > d.front().second) d.pop_front();
     }
     const T& top() {
         return d.front().first;
     }
};
