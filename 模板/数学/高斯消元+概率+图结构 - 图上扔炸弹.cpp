//2022.09.20
//一个无向图，节点1有一个炸弹，在每个单位时间内，有p/q的概率在这个节点炸掉，有1-p/q的概率随机选择一条出去的路到其他的节点上。问最终炸弹在每个节点上爆炸的概率。

#include<bits/stdc++.h>
using namespace std;
const int N=305;
const int M=5e4+5;
typedef double db;
int n,m;
db p,q,A[N][N];
vector<int>e[N];

void gau() {
	int r=1;
	for(int k=1; k<=n; k++) {
		int mr=r;
		for(int i=r+1; i<=n; i++) if(abs(A[mr][k])<abs(A[i][k])) mr=i;
		if(A[mr][k]==0) continue;
		for(int i=1; i<=n+1; i++) swap(A[r][i],A[mr][i]);
		
		for(int i=1; i<=n; i++) {
			if(i==r) continue;
			db mul=A[i][k]/A[r][k];
			for(int j=1; j<=n+1; j++) A[i][j]-=A[r][j]*mul;
		}
		r++;
	}
}

void ini() {
	for(int u=1; u<=n; u++) {
		A[u][u]=-1.0;
		int sz=e[u].size();
		for(int i=0; i<sz; i++) {
			int v=e[u][i];
			A[u][v]+=(1.0-p)/(1.0*(int)e[v].size());
		}
	}
	A[1][n+1]=-1;//划重点！为什么要赋值，为什么赋这个值！
}

int main() {
	scanf("%d%d%lf%lf",&n,&m,&p,&q);
	p=1.0*p/(1.0*q);
	for(int i=1,u,v; i<=m; i++) {
		scanf("%d%d",&u,&v);
		e[u].push_back(v), e[v].push_back(u);
	}
	e[0].push_back(1);
  
	ini();//准备系数，注意A[1][n+1]
	gau();
  
	for(int i=1; i<=n; i++) printf("%.8lf\n",A[i][n+1]*p/A[i][i]);
	return 0;
}
