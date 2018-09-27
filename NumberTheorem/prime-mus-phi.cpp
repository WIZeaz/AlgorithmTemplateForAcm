// 欧拉， 莫比乌斯函数， 质数线性筛
const int N=100000;
int prime[N+10]= {0},mus[N+10]= {0},num=0,phi[N+10]={0};
// prime-质数 mus-莫比乌斯函数 phi-欧拉函数
void pre() {
	mus[1]=1;
    phi[1]=0;
	for(int i=2; i<=N; i++) {
		if(!prime[i]){
			prime[++num]=i;
			mus[i]=-1;
			phi[i]=i-1;
		}
		for(int o=1; o<=num&&i<=N/prime[o]; o++) {
			prime[i*prime[o]]++;
			if(i%prime[o]==0){
				phi[i*prime[o]]=phi[i]*prime[o];
				break;
			}
			else {
				mus[i*prime[o]]=-mus[i];
				phi[i*prime[o]]=phi[i]*(prime[o]-1);
			}
		}
	}
}
