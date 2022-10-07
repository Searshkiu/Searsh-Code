//2022.09.23
//可持久化线段树/可持久化数值线段树/可持久化数组

#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,m,a[N],rt[N<<5];
struct stree{
	int ls,rs,x;
#define ls(y) t[y].ls
#define rs(y) t[y].rs
#define x(y) t[y].x  
}t[N<<5];//bound on tree
int ct;

void build(int &p,int lb,int rb){
	p=++ct;
	if(lb==rb){
		x(p)=a[lb];
		return;
	}
	int mid=lb+rb>>1;
	build(ls(p),lb,mid);
	build(rs(p),mid+1,rb);
}

void ins(int &p,int v,int lb,int rb,int x,int loc){//now version's root, history version's root
	p=++ct;
	ls(p)=ls(v), rs(p)=rs(v), x(p)=x(v);
	if(lb==rb){
		x(p)=x;
		return;
	}
	int mid=lb+rb>>1;
	if(loc<=mid) ins(ls(p),ls(v),lb,mid,x,loc);
	else ins(rs(p),rs(v),mid+1,rb,x,loc);
}

int qry(int &p,int lb,int rb,int loc){
	if(lb==rb) return x(p);
	int mid=lb+rb>>1;
	if(loc<=mid) return qry(ls(p),lb,mid,loc);
	else return qry(rs(p),mid+1,rb,loc);
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	build(rt[0],1,n);
	for(int i=1;i<=m;i++){
		int v,op,loc,x;
		scanf("%d%d%d",&v,&op,&loc);
		if(op==1){
			scanf("%d",&x);
			ins(rt[i],rt[v],1,n,x,loc);
		} else {
			printf("%d\n",qry(rt[v],1,n,loc));
			rt[i]=rt[v];
		}
	}
//	for(int i=0;i<=m;i++) printf("%d ",rt[i]);
	return 0;
}
