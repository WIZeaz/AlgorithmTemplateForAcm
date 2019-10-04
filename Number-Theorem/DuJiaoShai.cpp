#include <iostream>
#include <cstdio>
#include <map>
#include <unordered_map>
using namespace std;
typedef long long ll;
const int N = 5000000;
int prime[N + 10], mu[N + 10], phi[N + 10], isprime[N + 10];
int summu[N + 10];
ll sumphi[N + 10];
unordered_map<int, int> mapmu;
unordered_map<int, ll> mapphi;

void sieve(){
	mu[1]=phi[1]=1;
	for (int i = 2; i <= N; i++) {
		if (!isprime[i])
			prime[++prime[0]] = i, mu[i] = -1, phi[i] = i - 1;
		for (int o = 1; o <= prime[0] && prime[o] <= N / i; o++) {
			isprime[i * prime[o]]++;
			if (i % prime[o] == 0) {
				mu[i * prime[o]] = 0, phi[i * prime[o]] = phi[i] * prime[o];
				break;
			}
			mu[i * prime[o]] = -mu[i], phi[i * prime[o]] = phi[i] * phi[prime[o]];
		}
	}
	for (int i = 1; i <= N; i++)
		summu[i] = summu[i - 1] + mu[i], sumphi[i] = sumphi[i - 1] + phi[i];
}

int calmu(int x) {
	if (x <= N) return summu[x];
	if (mapmu[x]) return mapmu[x];
	int ans = 1;

	for (int l = 2, r; l <= x; l = r + 1) {
		r = x / (x / l);
		ans -= (r - l + 1) * calmu(x / l);
	}
	return mapmu[x] = ans;
}

ll calphi(int x) {
	if (x <= N) return sumphi[x];
	if (mapphi[x]) return mapphi[x];
	ll ans = 1ll * x * (x + 1) / 2;

	for (int i = 2, r; i <= x; i = r + 1) {
		r = x / (x / i);
		ans -= 1ll * (r - i + 1) * calphi(x / i);
	}
	return mapphi[x] = ans;
}

int main() {
	sieve();
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		// 求phi的前缀和跟mu的前缀和
		printf("%lld %d\n", calphi(n), calmu(n));
	}
}
