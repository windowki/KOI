#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int n, m, a[155];
int sum[155][155];
unsigned long long d[155][20000]; //1132500(max_score)/64bits

void process(void)
{
	int i, j, k;

	d[0][0] = 1ULL;
	for (i = 1; i <= n; i++)
	{
		for (j = 0; j <= sum[1][i - 1] / 64; j++)
			d[i][j] = d[i - 1][j];

		for (j = 1; j < i; j++)
			for (k = 0; k <= sum[1][j - 1]; k += 64)
			{
				//bit shift by sum[j + 1][i]
				d[i][(k + sum[j + 1][i]) / 64] |= (d[j - 1][k / 64] << (sum[j + 1][i] % 64));
				if(sum[j + 1][i] % 64)
					d[i][(k + sum[j + 1][i]) / 64 + 1] |= (d[j - 1][k / 64] >> (64 - sum[j + 1][i] % 64));
			}

		d[i][sum[1][i] / 64] |= 1ULL << (sum[1][i] % 64);
	}
}

int main()
{
	int i, j, s = 0;
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
		scanf("%d ", &a[i]);
	scanf("%d", &m);

	for (i = 1; i <= n; i++, s = 0)
		for (j = i; j <= n; j++)
		{
			s += a[j];
			sum[i][j] = sum[i][j - 1] + s;
		}
	if (m > sum[1][n])
	{
		printf("%d", m);
		return 0;
	}

	process();
	int x = m / 64, y = m % 64;
	unsigned long long temp;
	temp = d[n][x] >> y;
	for (i = m; ; i++)
	{
		if (!(temp & 1ULL))
		{
			printf("%d", i);
			return 0;
		}
		temp >>= 1;
		if (i % 64 == 63)
			temp = d[n][++x];
	}
}