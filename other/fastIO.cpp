#include <bits/stdc++.h>
using namespace std;
template <typename T> 
bool in(T& x){
    x = 0; T f = 1; char ch = cin.get();
    while (!isdigit(ch)) {
        if (ch == -1) return false;
        if (ch == '-') f = -1; 
        ch = cin.get();
    }
    while (isdigit(ch)) {x = x * 10 + ch - '0'; ch = cin.get();}
    x *= f; return true;
}
template <typename T, typename... S>
bool in(T& t, S&... s) {if(!in(t)) return false; return in(s...);}

namespace fastIO {
    const int BUF_SIZE = 100000;
    char buf[BUF_SIZE], *s, *t;
    inline char read() {
        if (s == t) {
            s = buf;
            t = buf + cin.rdbuf()->sgetn(buf, BUF_SIZE);
            if(s == t) return -1;
        }
        return *s++;
    }
    template <typename T> 
        bool in(T& x){
            x = 0; T f = 1; char ch = read();
            while (!isdigit(ch)) {
                if (ch == -1) return false;
                if (ch == '-') f = -1; 
                ch = read();
            }
            while (isdigit(ch)) {x = x * 10 + ch - '0'; ch = read();}
            x *= f; return true;
        }
    template <typename T, typename... S>
        bool in(T& t, S&... s) {if(!in(t)) return false; return in(s...);}

    const int OUT_LEN = 10000000;
    char obuf[OUT_LEN], *oh = obuf;
    inline void print(char c) {
        if (oh == obuf + OUT_LEN) cout.rdbuf()->sputn(obuf, OUT_LEN), oh = obuf;
        *oh++ = c;
    }
    inline void print(string& s) {
        for (auto i : s) print(i);
    }
    inline void print(const char* s) {
        while (*s) print(*s++);
    }
    template <typename T>
        void print(T x) {
            static int buf[30], cnt;
            if (x < 0) x = -x, print('-');
            cnt = 0;
            do {
                buf[++cnt] = x % 10 | 48;
                x /= 10;
            } while (x);
            while (cnt) print((char)buf[cnt--]);
        }
    template <typename T, typename... S>
        void print(T t, S... s) {print(t); print(s...);}

    inline void flush() { cout.rdbuf()->sputn(obuf, oh - obuf); }
};
using namespace fastIO;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    fastIO::flush();
}
