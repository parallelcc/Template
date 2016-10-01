#include<iostream>
#include<queue>
using namespace std;
typedef int datatype;
typedef struct node
{
    datatype data;
    struct node *lchild,*rchild; 
}bintnode;
typedef bintnode *bintree;

void createbintree(bintree &t)
{
//输入二叉树的先序遍历序列，创建二叉链表
    int ch;
    cin>>ch;
    if(ch==-1) t=NULL;//如果读入空格字符，创建空树； 
    else
    {
        t=new bintnode;
        t->data=ch;
        createbintree(t->lchild);//根据先序遍历，继续创建左子树，让客户端继续输入 
        createbintree(t->rchild);//创建完左子树，继续创建右子树 
    } //递归调用，自动返回
}
void preorder(bintree t)
{
    if(t)
    {
        cout<<t->data<<' ';//先访问根结点，再遍历左子树，跟着右子树 
        preorder(t->lchild);
        preorder(t->rchild);
    }
}
void inorder(bintree t)
{
    if(t)
	{
        inorder(t->lchild);
        cout<<t->data<<' ';
        inorder(t->rchild);
    }
}
void postorder(bintree t)
{
    if(t)
    {
        postorder(t->lchild);
        postorder(t->rchild);
        cout<<t->data<<' ';
    }
}
void levertravel(bintree t)
{
    queue<bintree> q;
    if(t!=NULL)
    q.push(t);
    bintree b;
    while(!q.empty())
    {
        b=q.front();
        cout<<b->data<<' ';
        q.pop();
        if(b->lchild) q.push(b->lchild);
        if(b->rchild) q.push(b->rchild);
	}
}
int main()
{
    bintree t=NULL;
    createbintree(t);
    cout<<"前序遍历: ";
    preorder(t);
    cout<<endl<<"中序遍历: ";
    inorder(t);
    cout<<endl<<"后序遍历: ";
    postorder(t);
    cout<<endl<<"层次遍历: ";
    levertravel(t);
    cout<<endl;
    return 0;
}
