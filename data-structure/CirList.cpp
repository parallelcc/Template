// Copyright 2017 Parallelc
#include <bits/stdc++.h>
using namespace std;  // NOLINT
template <typename T>
class CirList {
 public:
     class node {
      public:
          T data;
          node* nex;
          node* pre;
     };
     CirList() {
         __begin = nullptr;
         __size = 0;
     }
     explicit CirList(size_t n) {
         __size = 0;
         if (n == 0) __begin = nullptr;
         else {
             for (size_t i = n; i > 0; i--) {
                 insert(__begin, T(i));
             }
         }
     }
     node* const begin() const {return __begin;}
     const size_t size() const {return __size;}
     bool empty() const {return __size == 0;}
     node* insert(node* t, T s) {
         if (__size == 0) {
             t = new node;
             t->data = s;
             t->nex = t;
             t->pre = t;
             __begin = t;
         } else {
             t->pre->nex = new node;
             t->pre->nex->data = s;
             t->pre->nex->nex = t;
             t->pre->nex->pre = t->pre;
             t->pre = t->pre->nex;
             if (t == __begin) __begin = t->pre;
         }
         __size++;
         return t->pre;
     }
     node* erase(node* t) {
         if (__size == 0) return t;
         else if (__size == 1) {
             __begin = nullptr;
             delete t;
             __size--;
             return __begin;
         } else {
             if (t == __begin) __begin = t->nex;
             t->pre->nex = t->nex;
             t->nex->pre = t->pre;
             auto ans = t->nex;
             delete t;
             __size--;
             return ans;
         }
     }
     void clear() {
         while (erase(__begin) != nullptr) {}
     }
     ~CirList() {
         clear();
     }

 private:
     node* __begin;
     size_t __size;
};
