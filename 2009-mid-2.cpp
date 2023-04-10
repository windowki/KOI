#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX2(x,y) x>y ? x:y

int n, k, a[35];
int d[35][35];

int main()
{
	int i, j;
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
		scanf("%d ", &a[i]);
	scanf("%d", &k);

	//d[i][j]: switch i~n, bulb j~n
	for (i = 1; i <= n + 1; i++)
		d[n + 1][i] = d[i][n + 1] = 1;
	for (i = n; i >= 1; i--)
		for (j = n; j >= 1; j--)
		{
			if (j <= a[i])
				d[j][i] = d[a[i] + 1][i + 1] + d[j][i + 1];
			else
				d[j][i] = d[j][i + 1];
		}

	if (k > d[1][1])
	{
		printf("-1");
		return 0;
	}
	int row, col, sum=0;
	row = 1, col = 1;
	while (row<=n && col<=n && k>1) //k=1 correspond with i=n+1
	{
		for(i=n ; i>=col ; i--)
			if (d[row][i] >= k)
			{
				k-=d[row][i+1], sum |= (1<<(n-i));
				row = a[i] + 1;
				col = i+1;
				break;
			}
	}
	printf("%d", sum);
	return 0;
}