#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <algorithm>
#define MAX2(x,y) (x>y?x:y)
#define MIN2(x,y) (x>y?y:x)

using std::sort;
int x2, y3, x3, y2;
int k, n, a[100001][4]; //x1, y1, x2, y2 order. possible area of upper-right point for covering entire stain
int x[1000001], y[1000001];
int tree[530001], maxtree[530001], p; //identical values in the area, max value in the area
struct data {
	int x1, x2, y, inout;
} area[200001]; //not area, but point

bool compare(data& data1, data& data2)
{
	return (data1.y < data2.y || (data1.y == data2.y && data1.inout > data2.inout));
}

void update(int root, int left, int right, int query, int inout)
{
	if (area[query].x1 <= left && right <= area[query].x2)
		tree[root] += inout, maxtree[root] += inout;
	else
	{
		int mid = (left + right) / 2;
		if (area[query].x1 <= mid)
			update(root * 2, left, mid, query, inout);
		if (area[query].x2 > mid)
			update(root * 2 + 1, mid + 1, right, query, inout);

		maxtree[root] = tree[root] + MAX2(maxtree[root * 2], maxtree[root * 2 + 1]);
	}
}

int main()
{
	int i, ii, stain_x1, stain_y2, stain_x2, stain_y1, count = 0;
	scanf("%d %d %d %d", &x2, &y3, &x3, &y2);
	scanf("%d %d", &k, &n);
	for (i = 1; i <= n; i++)
	{
		scanf("%d %d %d %d", &stain_x1, &stain_y2, &stain_x2, &stain_y1);
		ii = i - count;
		a[ii][0] = MAX2(x2 + k, stain_x2);
		a[ii][1] = MAX2(y2 + k, stain_y2);
		a[ii][2] = MIN2(x3, stain_x1 + k);
		a[ii][3] = MIN2(y3, stain_y1 + k);
		if (a[ii][0] > a[ii][2] || a[ii][1] > a[ii][3])
			count++;
	}
	n -= count;
	for (i = 1; i <= n; i++)
		x[a[i][0]] = x[a[i][2]] = 1, y[a[i][1]] = y[a[i][3]] = 1;
	int xcount = 0, ycount = 0;
	for (i = x2; i <= x3; i++)
		if (x[i])
			x[i] = ++xcount;
	for (i = y2; i <= y3; i++)
		if (y[i])
			y[i] = ++ycount;
	ii = 0;
	for (i = 1; i <= n; i++)
	{
		ii++;
		area[ii].x1 = x[a[i][0]], area[ii].x2 = x[a[i][2]];
		area[ii].y = y[a[i][1]], area[ii].inout = 1;
		ii++;
		area[ii].x1 = x[a[i][0]], area[ii].x2 = x[a[i][2]];
		area[ii].y = y[a[i][3]], area[ii].inout = -1;
	}
	sort(area + 1, area + 2 * n + 1, compare);

	p = 1;
	while (p < xcount)
		p *= 2;

	int line, maax = 0;
	i = 1;
	while (i <= 2 * n)
	{
		line = area[i].y;
		while (area[i].y == line && area[i].inout == 1)
		{
			update(1, 1, p, i, 1);
			i++;
		}
		if (maax < maxtree[1])
			maax = maxtree[1];
		line = area[i].y;
		while (area[i].y == line && area[i].inout == -1)
		{
			update(1, 1, p, i, -1);
			i++;
		}
	}
	printf("%d", maax);
	return 0;
}