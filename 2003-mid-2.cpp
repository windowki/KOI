#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX2(x,y) (x>y?x:y)
#define INF 9999999

int l, n, a[1001][2];
int d[1001][1001]; //last index i from (1,1), last index j from (l,l)
int path[1001][1001][2];
int min = INF, i1, i2, check[1001];

int get_distance(int x1, int y1, int x2, int y2)
{
	return MAX2(x1 - x2, x2 - x1) + MAX2(y1 - y2, y2 - y1);
}

int main()
{
	int i, j, k, x, y;
	scanf("%d %d", &l, &n);
	for (i = 1; i <= n; i++)
		scanf("%d %d", &a[i][0], &a[i][1]);

	for (i = 0; i <= n; i++)
		for (j = 0; j <= n; j++)
			d[i][j] = INF, path[i][j][0] = path[i][j][1] = -1;

	d[0][0] = 0;
	d[1][0] = get_distance(1, 1, a[1][0], a[1][1]), path[1][0][0] = 0;
	d[0][1] = get_distance(l, l, a[1][0], a[1][1]), path[0][1][1] = 0;

	for (i = 2; i <= n; i++)
	{
		d[i][0] = d[i - 1][0] + get_distance(a[i - 1][0], a[i - 1][1], a[i][0], a[i][1]);
		path[i][0][0] = i - 1;
		d[0][i] = d[0][i - 1] + get_distance(a[i - 1][0], a[i - 1][1], a[i][0], a[i][1]);
		path[0][i][1] = i - 1;
	}

	for (k = 2; k <= n; k++)
	{
		//[k,k-1]
		for (i = 0; i <= k - 2; i++)
		{
			x = a[i][0], y = a[i][1];
			if (i == 0)
				x = 1, y = 1;
			if (d[k][k - 1] > d[i][k - 1] + get_distance(x, y, a[k][0], a[k][1]))
			{
				d[k][k - 1] = d[i][k - 1] + get_distance(x, y, a[k][0], a[k][1]);
				path[k][k - 1][0] = i;
			}
		}
		//[k-1,k]
		for (j = 0; j <= k - 2; j++)
		{
			x = a[j][0], y = a[j][1];
			if (j == 0)
				x = l, y = l;
			if (d[k - 1][k] > d[k - 1][j] + get_distance(x, y, a[k][0], a[k][1]))
			{
				d[k - 1][k] = d[k - 1][j] + get_distance(x, y, a[k][0], a[k][1]);
				path[k - 1][k][1] = j;
			}
		}
		//remain
		for (i = k + 1; i <= n; i++)
		{
			d[i][k - 1] = d[i - 1][k - 1] + get_distance(a[i - 1][0], a[i - 1][1], a[i][0], a[i][1]);
			path[i][k - 1][0] = i - 1;
			d[k - 1][i] = d[k - 1][i - 1] + get_distance(a[i - 1][0], a[i - 1][1], a[i][0], a[i][1]);
			path[k - 1][i][1] = i - 1;
		}
	}

	for (i = 0; i <= n; i++)
	{
		if (min > d[i][n])
			min = d[i][n], i1 = i, i2 = n;
		if (min > d[n][i])
			min = d[n][i], i1 = n, i2 = i;
	}
	printf("%d\n", min);
	while (i1 || i2)
	{
		x = path[i1][i2][0], y = path[i1][i2][1];
		if (x != -1)
			check[i1] = 1, i1 = x;
		else
			check[i2] = 2, i2 = y;
	}
	for (i = 1; i <= n; i++)
		printf("%d\n", check[i]);
	return 0;
}