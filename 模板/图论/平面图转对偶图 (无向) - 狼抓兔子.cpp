//2022.09.22

#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
#define fs first
#define sc second
const int N=1e6+5;
const int NE=6e6+6;
typedef long long ll;
int n,m;
int S,T;
struct edge{
	int v,nxt;
	ll w;
	edge(){}
	edge(int _v,ll _w,int _nxt){
		v=_v, w=_w, nxt=_nxt;
	}
}e[NE];
int h[NE],ce;
ll d[NE];

void ade(int u,int v,ll w){
	e[++ce]=edge(v,w,h[u]);
	h[u]=ce;
}

inline int cal(int x,int y){
	if(x<1 || y==m) return T;
	if(x==n || y<1) return S;
	return (x-1)*(m-1)+y;
}

inline int cal2(int x,int y){
	int c=cal(x,y);
	if(c==S) return S;
	if(c==T) return T;
	return c+(n-1)*(m-1);
}

bool vis[NE];
void dij(){
	int u,v;
	ll w;	
	memset(vis,false,sizeof(vis));
	memset(d,0x3f,sizeof(d));
	priority_queue< pair<ll,int> >q;
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
				if(!vis[v]) q.push(mp(-d[v],v));
			}
		}
	}
  
}

int main(){
	scanf("%d%d",&n,&m);
	S=0;//自建源点，左下角
	T=2*(m-1)*(n-1)+1;//自建汇点，右上角
	for(int i=1;i<=n;i++){
		for(int j=1;j<m;j++){
			ll w;
			scanf("%lld",&w);
			ade(cal(i,j),cal2(i-1,j),w), ade(cal2(i-1,j),cal(i,j),w);
		}
	}
  //加跨竖线的边
	for(int i=1;i<n;i++){
		for(int j=1;j<=m;j++){
			ll w;
			scanf("%lld",&w);
			ade(cal(i,j-1),cal2(i,j),w), ade(cal2(i,j),cal(i,j-1),w);
		}
	}
//加跨斜线的边
	for(int i=1;i<n;i++){
		for(int j=1;j<m;j++){
			ll w;
			scanf("%lld",&w);
			ade(cal(i,j),cal2(i,j),w), ade(cal2(i,j),cal(i,j),w);
		}
	}
  
	dij();
	printf("%lld",d[T]);
	return 0;
}
