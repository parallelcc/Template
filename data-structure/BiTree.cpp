#include <bits/stdc++.h>
using namespace std;
template <typename T>
class BiTree {
 public:
     T data;
     BiTree* lchild;
     BiTree* rchild; 
     BiTree() {
         this->data = -1;
         lchild = nullptr;
         rchild = nullptr;
     }
     void insert(T data) {
         if (this->data == -1) {
             this->data = data;
             this->lchild = new BiTree;
             this->rchild = new BiTree;
         } else if (data < this->data) {
             this->lchild->insert(data);
         } else {
             this->rchild->insert(data);
         }
     }
     void create() {
         T data;
         cin >> data;
         this->data = data;
         if(data != -1) {
             lchild = new BiTree;
             rchild = new BiTree;
             lchild->create();
             rchild->create();
         }
     }
     void preorder() {
         cout << this->data << ' ';
         if (this->lchild->data != -1) this->lchild->preorder();
         if (this->rchild->data != -1) this->rchild->preorder();
     }
     void inorder() {
         if (this->lchild->data != -1) this->lchild->inorder();
         cout << this->data << ' ';
         if (this->rchild->data != -1) this->rchild->inorder();
     }
     void postorder() {
         if (this->lchild->data != -1) this->lchild->postorder();
         if (this->rchild->data != -1) this->rchild->postorder();
         cout << this->data << ' ';
     }
     void level() {
         queue<BiTree*> q;
         q.push(this);
         BiTree* b;
         while(!q.empty()) {
             b = q.front();
             cout << b->data;
             q.pop();
             if(b->lchild->data != -1) q.push(b->lchild);
             if(b->rchild->data != -1) q.push(b->rchild);
             if (!q.empty()) cout << ' ';
         }
         cout << '\n';
     }
};
