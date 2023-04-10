#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define INF -999999999
#define MAX2(x,y) (x>y? x:y)

int n, a[1005][1005];
int d[1005][1005][2]; //0: from left, 1: from right

int main()
{
	int i, j, temp;
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
		{
			scanf("%d ", &a[i][j]);
			d[i][j][0] = d[i][j][1] = INF;
		}

	for (i = 1; i <= n; i++)
		d[1][i][0] = d[1][i - 1][0] + a[1][i];

	for (i = 2; i <= n; i++)
	{
		//from up or left
		d[i][1][0] = MAX2(d[i - 1][1][0], d[i - 1][1][1]) + a[i][1];
		for (j = 2; j <= n; j++)
		{
			d[i][j][0] = d[i][j - 1][0];
			temp = MAX2(d[i - 1][j][0], d[i - 1][j][1]);
			d[i][j][0] = MAX2(d[i][j][0], temp) + a[i][j];
		}

		//from up or right
		d[i][n][1] = MAX2(d[i - 1][n][0], d[i - 1][n][1]) + a[i][n];
		for (j = n - 1; j >= 1; j--)
		{
			d[i][j][1] = d[i][j + 1][1];
			temp = MAX2(d[i - 1][j][0], d[i - 1][j][1]);
			d[i][j][1] = MAX2(d[i][j][1], temp) + a[i][j];
		}
	}

	printf("%d", MAX2(d[n][n][0], d[n][n][1]));
	return 0;
}