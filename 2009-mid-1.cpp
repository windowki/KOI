#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int n, count[10005];
long long sum;

int main()
{
	int i, temp;
	scanf("%d ", &n);
	for (i = 1; i <= n; i++)
		scanf("%d", &temp), count[temp]++, sum+=(long long)temp;
	
	int cnt = 0, flag = 0;
	for (i = 1; i <= 10000; i++)
	{
		temp = count[i];
		while (temp)
		{
			temp--, cnt++;
			if (cnt == (n + 1) / 2)
			{
				printf("%d ", i), flag=1;
				break;
			}
		}
		if (flag)
			break;
	}
	
	double min_square;
	long long min1, min2, sum1=0, sum2=0;
	min_square = (double)sum / n;
	min1 = (long long)min_square, min2 = min1 + 1;
	for (i = 1; i <= 10000; i++)
		sum1 += count[i] * (min1 - i) * (min1 - i), sum2 += count[i] * (min2 - i) * (min2 - i);
	printf("%lld", sum1 <= sum2 ? min1 : min2);
	return 0;
}