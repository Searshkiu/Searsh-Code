朴素Dinic + 当前弧。

求下图的最大流：源点为 S，汇点为 T，包括源汇总共 n+2 个点。S 向 i 连边，流量为 ai；i 向 T 连边，流量为 bi；i 向 pi 连边，流量为 ci。

输入格式
第一行一个整数 n，表示除了源汇的节点个数。
第二行 n 个整数 pi，表示每个点的出边。
第三行 n 个整数 ai，表示源点到每个点的流量。
第四行 n 个整数 bi，表示每个点到汇点的流量。
第五行 n 个整数 ci，表示 i 到 pi 的流量。

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5;
const int M=(N<<2);
const ll INF=1e18+7;
int n,s,t,p[N];
struct edge{
	int v,nxt;
	ll w;
	edge(){}
	edge(int _v,ll _w,int _nxt){
		v=_v, w=_w, nxt=_nxt;
	}
}e[M<<1];
int ce=1,h[N],dep[N];

inline void ade(int u,int v,ll w){
	e[++ce]=edge(v,w,h[u]);
	h[u]=ce;
}

inline bool bfs(){
	queue<int>q;
	memset(dep,0,sizeof(dep));
	dep[s]=1;
	q.push(s);
	int u,v;
	while(q.size()){
		u=q.front(); q.pop();
		for(int i=h[u];i;i=e[i].nxt){
			v=e[i].v;
			if(e[i].w && !dep[v]){
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
	return dep[t];
}

ll dfs(int u,ll f){
	if(u==t) return f;
	ll ret=0;
	for(int i=h[u],v;i;i=e[i].nxt){
		v=e[i].v;
		if(e[i].w==0 || dep[v]!=dep[u]+1) continue;
		ll ex=dfs(v,min(f,e[i].w));
		e[i].w-=ex, e[i^1].w+=ex;
		ret+=ex, f-=ex;
		if(!f) break;
	}
	if(!ret) return dep[u]=0;
	return ret;
}

int main(){
	scanf("%d",&n);
	s=n+1, t=n+2;
	for(int i=1;i<=n;i++) scanf("%d",&p[i]);
	for(int i=1;i<=n;i++){
		ll a;
		scanf("%lld",&a);
		ade(s,i,a), ade(i,s,0);
	}
	for(int i=1;i<=n;i++){
		ll b;
		scanf("%lld",&b);
		ade(i,t,b), ade(t,i,0);
	}
	for(int i=1;i<=n;i++){
		ll c;
		scanf("%lld",&c);
		ade(i,p[i],c), ade(p[i],i,0);
	}
	ll ans=0;
	while(bfs()){
		ans+=dfs(s,INF);
	}
	printf("%lld\n",ans);
	return 0;
}
```
