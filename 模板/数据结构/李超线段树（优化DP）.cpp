//https://www.luogu.com.cn/problem/P4655
//#define _GLIBCXX_DEBUG
#include<bits/stdc++.h>
using namespace std;
#define fr(i,l,r) for(int i=(l);i<=(r);i++)
typedef long long ll;
const int N=1e5+5;
const ll H=1e6+5;
int n;
ll h[N],s[N];
ll k[N],b[N],f[N];
int id[H<<2];

inline ll ln(int t,ll x){
	return k[t]*x+b[t];
}

void upd(int p,ll l,ll r,int t){
	if(l==r){
		if(ln(id[p],l)>ln(t,l)) id[p]=t;
		return;
	}
	ll mid=l+r>>1;
	if(ln(id[p],mid)>ln(t,mid)) swap(id[p],t);
	ll vpl=ln(id[p],l),vpr=ln(id[p],r),vtl=ln(t,l),vtr=ln(t,r);
	if(vtl<vpl) upd(p<<1,l,mid,t);
	else if(vtr<vpr) upd(p<<1|1,mid+1,r,t);
}

ll qry(int p,ll l,ll r,ll x){
	ll res=ln(id[p],x);
	if(l==r) return res;
	ll mid=l+r>>1;
	if(x<=mid) return min(res,qry(p<<1,l,mid,x));
	return min(res,qry(p<<1|1,mid+1,r,x));
}

int main(){
	scanf("%d",&n);
	fr(i,1,n) scanf("%lld",&h[i]);
	fr(i,1,n) scanf("%lld",&s[i]), s[i]+=s[i-1];
	
	k[1]=-2ll*h[1], b[1]=h[1]*h[1]-s[1];
	b[0]=H*H, upd(1,1,H,1);
	fr(i,2,n){
		f[i]=h[i]*h[i]+s[i-1]+qry(1,1,H,h[i]);
		k[i]=-2ll*h[i], b[i]=f[i]+h[i]*h[i]-s[i];
		upd(1,1,H,i);
	}
	
	printf("%lld\n",f[n]);
	return 0;
}
