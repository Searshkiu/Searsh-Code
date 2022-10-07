//2022.09.20
//如果有唯一解，则输出解（小数点后保留两位小数）。如果方程组无解输出 −1； 如果有无穷多实数解，输出 0；

#include<bits/stdc++.h>
using namespace std;
const int N=55;
typedef double db;
const db eps=1e-8;
int n;
db A[N][N];

void gau(){
	int r=1;//current row
	for(int k=1;k<=n;k++){//now index
		int mr=r;
		for(int i=r+1;i<=n;i++) if(abs(A[i][k])>abs(A[mr][k])) mr=i;
		if(A[mr][k]==0) continue;
//		for(int i=1;i<=n+1;i++) printf("%lf %lf\n",A[r][i],A[mr][i]);
		for(int i=1;i<=n+1;i++) swap(A[r][i],A[mr][i]);
//		for(int i=1;i<=n+1;i++) printf("%lf\n",A[r][i]);
		
//		printf("kkk%d\n",k);
		for(int i=1;i<=n;i++){
			if(i==r) continue;
//			printf("i %d\n",i);
			db mul=A[i][k]/A[r][k];
//			printf("%lf ii%d\n",A[r][k], i);
			for(int j=k+1;j<=n+1;j++) A[i][j]-=A[r][j]*mul;
		}
		r++;
	}
  
	if(r<=n){
		while(r<=n){
			if(A[r][n+1]!=0){//系数都是0，但右边值不为0，无解
				printf("-1");
				return;
			}
			r++;
		}
		printf("0");//有一条系数都是0且右边值是0的式子，无穷解
		return;
	}
  
	for(int i=1;i<=n;i++){
		if(int(A[i][n+1]/A[i][i]*100)==0) printf("x%d=0.00\n",i);
		else printf("x%d=%.2lf\n",i,A[i][n+1]/A[i][i]);
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n+1;j++) scanf("%lf",&A[i][j]), A[i][j]*=1.0;
	}
	gau();
	return 0;
}
