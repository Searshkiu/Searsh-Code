//2022.09.24

#include<bits/stdc++.h>
using namespace std;
#define sc second
#define mp make_pair
const int INF=1e9;
const int N=3e3+3;
const int M=6e3+3;
int n,m;
typedef long long ll;
struct edge{
	int v,nxt;
	ll w;
	edge(){}
	edge(int _v,ll _w,int _nxt){
		v=_v, w=_w, nxt=_nxt;
	}
}e[M<<1];
int ce,h[N];
void ade(int u,int v,ll w){
	e[++ce]=edge(v,w,h[u]);
	h[u]=ce;
}

ll f[N];
bool vis[N];
bool spfa(){
	int t[N];
	memset(t,0,sizeof(t));
	for(int i=1;i<=n;i++) f[i]=INF;
	memset(vis,0,sizeof(vis));
	queue<int>q;
	f[0]=0, q.push(0), vis[0]=true;
	while(q.size()){
		int u=q.front(); q.pop();
		vis[u]=false;
		for(int i=h[u];i;i=e[i].nxt){
			int v=e[i].v;
			ll w=e[i].w;
			if(f[v]>f[u]+w){
				f[v]=f[u]+w, t[v]=t[u]+1;
				if(t[v]==n+1) return false;
				if(!vis[v]){
					vis[v]=true, q.push(v);
				}
			}
		}
	}
	return true;
}

ll d[N];
void dij(int s){
//	printf("[%d]\n",h[s]);
	priority_queue< pair<ll,int> >q;
	for(int i=1;i<=n;i++) d[i]=INF;
	memset(vis,false,sizeof(vis));
	d[s]=0;
	q.push(mp(0,s));
	int u,v; ll w;
	while(!q.empty()){
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
	for(int i=1,u,v;i<=m;i++){
		ll w;
		scanf("%d%d%lld",&u,&v,&w);
		ade(u,v,w);
	} 
	for(int i=1;i<=n;i++) ade(0,i,0);
//	printf("edge added\n");
	if(!spfa()){
		printf("-1");
		return 0;
	}
//	printf("spfa done\n");
	for(int i=1;i<=n;i++){
		for(int j=h[i];j;j=e[j].nxt){
			e[j].w+=f[i]-f[e[j].v];
		}
	}
	for(int i=1;i<=n;i++){
		dij(i);
		ll ans=0;
		for(int j=1;j<=n;j++) d[j]==INF ? ans+=1ll*j*INF: ans+=1ll*j*(d[j]+f[j]-f[i]);
		printf("%lld\n",ans);	
	}

	return 0;
}
