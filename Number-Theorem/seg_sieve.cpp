typedef long long ll;
const int N=1e5+10;
bool prime_small[N+10],prime[N+10];
// 筛[l,r]之间的素数个数
int seg_sieve(ll l,ll r){
	for(ll i=0;i*i<=r;i++)prime_small[i]=true;
	for(int i=0;i<=r-l;i++)prime[i]=true;
	for(ll i=2;i*i<=r;i++)
		if(prime_small[i]){
			for(ll o=2*i;o*o<=r;o+=i)prime_small[o]=false;
			for(ll o=max(2ll,(l+i-1)/i)*i;o<=r;o+=i)prime[o-l]=false;
		}

	int ans=0;
	for(int i=0;i<=r-l;i++)if(prime[i])ans++;
	if(l==1)ans--;
	return ans;
}
