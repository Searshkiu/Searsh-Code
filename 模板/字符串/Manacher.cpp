//2022.09.29

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e7+5;
int n;
char s[N],A[N<<1];
int ra[N<<1],ans;

void man(char *s, int *d){
	int r=0,c=0;//center
	for(int i=1;i<=2*n+1;i++){
		if(i<=r) d[i]=min(r-i+1,d[c*2-i]);
		while(i-d[i] && i+d[i]<=2*n+1 && s[i-d[i]]==s[i+d[i]]) d[i]++;
		if(i+d[i]>r) r=i+d[i]-1,c=i;
		ans=max(ans,d[i]-1);
	}
}

int main(){
	scanf(" %s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++){//2~2n+1
		A[i*2]=s[i], A[i*2+1]='#';
	}
	A[1]='#';
	man(A,ra);

	printf("%d",ans);
	return 0;
}
