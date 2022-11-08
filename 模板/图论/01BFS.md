ZhengruiOI NOIP2022冲刺day18-B-Graph

Cuber QQ 会给你一张包含 n 个点 m 条边的有向图，每个点 x 都有一个权值 vx，每条边的长度均为 1。

现在 Cuber QQ 会根据点的权值在图中增加一些有向边，如果顶点 x 和 y 满足 vx and vy=vy ，则增加一条从 x 到 y 的有向边。

现在 Cuber QQ 想知道从 1 号顶点出发，到其他所有顶点的最短路径的长度。

---

【1】虚点要少一个1的**全部加完**，因为它们很有可能只是作为**桥梁**通向存在的点。
【2】虚点的`dis`记得更新。
【3】用到再加。
【4】空间记得**O(V+E)**
【5】这是贪心实现优先队列。因为BFS的特殊性质，每个点只入队一次，所以只入队更新了的点，这里不需要`vis`.

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
const int E=1<<20;
const int INF=0x3f3f3f3f;
int n,m,s,a;
#define pr pair<int,int>
#define mp make_pair
#define fs first
#define sc second
vector< pr >e[N+E+2];
#define pb push_back

int d[N+E+2];
void bfs() {
	deque<int>q;
	memset(d,0x3f,sizeof(d));
	d[s]=0;
	q.push_back(s);
	int u,v,w;
	while(!q.empty()) {
		u=q.front();
		q.pop_front();
		for(auto i:e[u]) {
			v=i.fs,w=i.sc;
			if(d[v]>d[u]+w) {
				d[v]=d[u]+w;
				if(!w) q.push_front(v);
				else q.pb(v);
			}
		}
		if(u>n) {
			int i=u-n-1;
			for(int j=0; j<21; j++) {
				if(((i>>j)&1) && (i!=(1<<j))) {
					int to=(i^(1<<j));
					if(d[n+to+1]>d[u]) d[n+to+1]=d[u], q.push_front(n+to+1);
				}
			}
		}
	}
}

int main() {
	freopen("sample2.in","r",stdin);
	freopen("test.out","w",stdout);

	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++) {
		scanf("%d",&a);
		e[i].pb(mp(n+a+1,1)), e[n+a+1].pb(mp(i,0));
	}
	for(int i=1,u1,v1; i<=m; i++) {
		scanf("%d%d",&u1,&v1);
		e[u1].pb(mp(v1,1));
	}
	s=1;
	bfs();
	for(int i=1; i<=n; i++) printf("%d\n",(d[i]<INF?d[i]:-1));
	return 0;
}
```
