// h(x) <= h*(x) 
// --h(x) - h(x + 1) <= g(x + 1) - g(x)
#include<bits/stdc++.h>
using namespace std;
struct node{
	//status
	int x;
	//value
	int f, g, h;
	bool operator < (node a) const {return f > a.f;}
};
int close[];//if in close or not
int re[];//node's f in open or close
void update(node &e){//update e.f
	e.h = ;
	e.f = e.g + e.h;
}
int main(){
	//some var

	//main program
	while(~scanf()){
		//init 
		scanf();
		for (){
			re[] = 0x3f3f3f3f;
			close[] = 0;
		}
		//start
		node e, d;//current node and new node
		e.x = ;
		e.g = 0;
		update(e);
		re[e.x] = e.f;
		priority_queue<node> q;
		q.push(e);
		while (!q.empty()){
			do{
				e = q.top();
				q.pop();
			}while(!q.empty()&&close[e.x]);
			if (close[e.x] == 0){
				close[e.x] = 1;
				if (/*end*/) break;
				for (){
					d.x = ;
					d.g = e.g + ;
					update(d);
					if (re[d.x] > d.f){
						q.push(d);
						re[d.x] = d.f;
						close[d.x] = 0;
					}
				}
			}
		}
		if (close[e.x]) printf("%d\n", e.g);
		else printf("-1\n");
	}
	return 0;
}
