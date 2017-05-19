#include<iostream>
#include<cstdio>
#include<deque>
using namespace std;
int a[1000006];
int main(){
    int n, k;
    deque<int> d;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++){
        scanf("%d", &a[i]);
        while (!d.empty() && a[d.back()] >=  a[i]) d.pop_back();
        d.push_back(i);
        if (i >= k - 1){
            if (i - k >= d.front()) d.pop_front();
            printf("%d%c", a[d.front()], i == n - 1? '\n':' ');
        }
    }
    d.clear();
    for (int i = 0; i < n; i++){
        while(!d.empty() && a[d.back()] <= a[i]) d.pop_back();
        d.push_back(i);
        if (i >= k - 1){
            if (i - k >= d.front()) d.pop_front();
            printf("%d%c", a[d.front()], i == n - 1? '\n':' ');
        }
    }
}
