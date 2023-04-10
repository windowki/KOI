#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int n, a[20005], idx[20005], check[20005];
long long cycle, ans = 1;

int process(int arr, int i, int lev)
{
	if (check[arr])
		return lev;
	else
	{
		check[arr] = 1;
		return process(i, idx[i],lev+1);
	}
}

long long lcm(long long n1, long long n2)
{
	long long temp, m1 = n1, m2 = n2;
	while (m1)
	{
		if (m1 < m2)
			temp = m1, m1 = m2, m2 = temp;
		m1 %= m2;
	}
	return n1*n2/m2;
}

int main()
{
	int i;
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
		scanf("%d ", &a[i]), idx[a[i]] = i;
	for(i=1 ; i<=n ; i++)
		if (!check[a[i]])
		{
			cycle = (long long)process(a[i],i,0);
			ans = lcm(ans,cycle);
		}
	printf("%lld", ans);
	return 0;
}