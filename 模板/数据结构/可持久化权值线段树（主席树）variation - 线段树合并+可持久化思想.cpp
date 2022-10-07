//线段树合并+可持久化思想

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

void ins(int &p,int lb,int rb,int x){
	if(!p) p=++ct;
	s(p)++;
	if(lb==rb) return;
	int mid=lb+rb>>1;
	if(x<=mid) ins(ls(p),lb,mid,x);
	else ins(rs(p),mid+1,rb,x); 
}

int mg(int p1,int p2){
	if(!p1 || !p2) return p1|p2;
	int x=++ct;
	s(x)=s(p1)+s(p2);
	ls(x)=mg(ls(p1),ls(p2));
	rs(x)=mg(rs(p1),rs(p2));
	return x;
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
	for(int i=1;i<=n;i++) ins(rt[i],1,cnt,lower_bound(b+1,b+cnt+1,a[i])-b);
	for(int i=1;i<=n;i++) rt[i]=mg(rt[i],rt[i-1]);
	while(m--){
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",qry(rt[l-1],rt[r],1,cnt,k));
	}
	return 0;
}
