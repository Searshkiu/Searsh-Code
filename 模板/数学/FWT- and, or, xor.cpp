#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1<<17|1;
const int M=998244353;
int n,x;
ll A[N],B[N],a[N],b[N];

inline void ini(){ for(int i=0;i<=x;i++) a[i]=A[i], b[i]=B[i]; }

inline void orw(ll *f, ll tg){
	for(int o=2,k=1;o<=x;o<<=1, k<<=1){
		for(int i=0;i<x;i+=o)
		for(int j=0;j<k;j++)
			f[i+j+k]=(f[i+j+k]+f[i+j]*tg%M)%M;
	}
}

inline void andw(ll *f, ll tg){
	for(int o=2,k=1;o<=x;o<<=1, k<<=1){
		for(int i=0;i<x;i+=o)
		for(int j=0;j<k;j++)
			f[i+j]=(f[i+j]+f[i+j+k]*tg%M)%M;
	}
}

inline void xorw(ll *f, ll tg){
	for(int o=2,k=1;o<=x;o<<=1, k<<=1){
		for(int i=0;i<x;i+=o)
		for(int j=0;j<k;j++){
			f[i+j]=(f[i+j]+f[i+j+k])%M;
			f[i+j+k]=((f[i+j]-f[i+j+k]+M)%M -f[i+j+k]+M)%M;
			f[i+j]=(f[i+j]*tg+M)%M, f[i+j+k]=(f[i+j+k]*tg+M)%M;
		}
	}
}

inline void cal(){ for(int i=0;i<x;i++) a[i]=(a[i]*b[i])%M; }

inline void out(){ for(int i=0;i<x;i++) printf("%lld ",a[i]); printf("\n"); }

inline void OR(){
	ini(),orw(a,1),orw(b,1),cal(),orw(a,M-1);
	out();
}
inline void AND(){
	ini(),andw(a,1),andw(b,1),cal(),andw(a,M-1);
	out();
}
inline void XOR(){
	ini(),xorw(a,1),xorw(b,1),cal(),xorw(a,(M+1)>>1);
	out();
}
int main(){
	scanf("%d",&n);
	x=1<<n;
	for(int i=0;i<x;i++) scanf("%lld",&A[i]),A[i]%=M;
	for(int i=0;i<x;i++) scanf("%lld",&B[i]),B[i]%=M;
	OR(),AND(),XOR();
	return 0;
}

