//2022.09.22
//原图从左上到右下，对偶图全体逆时针转90°

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define mp make_pair
#define sc second
const int N=505;
int n,S,T;
struct edge{
	int v,nxt;
	ll w;
	edge(){}
	edge(int _v,ll _w,int _nxt){
		v=_v, w=_w, nxt=_nxt;
	}
}e[N*N*4];
int h[N*N],ce;

int cal(int x,int y){
	if(x==n+1 || y<1) return S;
	if(x<1|| y==n+1) return T;
	return (x-1)*n+y;
}

bool vis[N*N];
ll d[N*N];
void dij(){
	priority_queue< pair<ll,int> >q;
	memset(d,0x3f,sizeof(d));
	memset(vis,false,sizeof(vis));
	int u,v; ll w;
	d[S]=0;
	q.push(mp(0,S));
	while(q.size()){
		u=q.top().sc; q.pop();
		if(vis[u]) continue;
		vis[u]=true;
		for(int i=h[u];i;i=e[i].nxt){
			v=e[i].v, w=e[i].w;
			if(d[v]>d[u]+w){
				d[v]=d[u]+w;
				q.push(mp(-d[v],v));
			}
		}
	}
}

void ade(int u,int v,ll w){
	e[++ce]=edge(v,w,h[u]);
	h[u]=ce;
}

void read(){
	ll w;
	for(int i=1;i<=n+1;i++){
		for(int j=1;j<=n;j++) scanf("%lld",&w), ade(cal(i,j),cal(i-1,j),w);//跨横//hg[i][j]=w;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n+1;j++) scanf("%lld",&w), ade(cal(i,j-1),cal(i,j),w);//跨竖//sh[i][j]=w;
	}
	for(int i=1;i<=n+1;i++){
		for(int j=1;j<=n;j++) scanf("%lld",&w), ade(cal(i-1,j),cal(i,j),w);//hg[i][j]-=w;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n+1;j++) scanf("%lld",&w), ade(cal(i,j),cal(i,j-1),w);//sh[i][j]-=w;
	}
}

int main(){
	scanf("%d",&n);
	S=0, T=n*n+1;
	read();
	dij();
	printf("%lld",d[T]);
	return 0;
}
