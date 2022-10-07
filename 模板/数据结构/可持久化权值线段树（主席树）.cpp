// ver 1, 主席树板子
//2022.09.23

#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m,a[N],b[N];
struct segt{
	int ls,rs,s;
	#define ls(x) t[x].ls
	#define rs(x) t[x].rs
	#define s(x) t[x].s
}t[N<<5];
int ct;
int rt[N];

int build(int lb,int rb){
	int ret=++ct;
	if(lb==rb) return ret;
	int mid=lb+rb>>1;
	ls(ret)=build(lb,mid);
	rs(ret)=build(mid+1,rb); 
	return ret;
}

int ins(int p,int lb,int rb,int x){
	int ret=++ct;
	ls(ret)=ls(p), rs(ret)=rs(p), s(ret)=s(p)+1;
	if(lb==rb) return ret;
	int mid=lb+rb>>1;
	if(x<=mid) ls(ret)=ins(ls(p),lb,mid,x);
	else rs(ret)=ins(rs(p),mid+1,rb,x);
	return ret;
}

int qry(int p1,int p2,int lb,int rb,int k){
	if(lb==rb) return b[lb];
	int mid=lb+rb>>1;
	int s=s(ls(p2))-s(ls(p1));
	if(k<=s) return qry(ls(p1),ls(p2),lb,mid,k);
	else return qry(rs(p1),rs(p2),mid+1,rb,k-s);
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]), b[i]=a[i];
	sort(b+1,b+n+1);
	int cnt=unique(b+1,b+n+1)-b-1;
//	printf("cnt=%d\n",cnt);
	rt[0]=build(1,cnt);
	for(int i=1;i<=n;i++) rt[i]=ins(rt[i-1],1,cnt,lower_bound(b+1,b+cnt+1,a[i])-b);
	while(m--){
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",qry(rt[l-1],rt[r],1,cnt,k));
	}
	return 0;
}
