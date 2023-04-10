#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <queue>
#include <algorithm>
#define EPSILON 0.00000001

int n;
long long a[1015][4], l;
double d[1015][1015]; //distance from start to intersection (0: INF)
bool check[1015][1015]; //whether i snail can reach j snail in the future

using namespace std;
typedef pair<double, pair<int, int> > ppair;
priority_queue<ppair, vector<ppair>, greater<ppair> > q;

double abso(double num)
{
	return num > 0 ? num : -num;
}

void cross_check(int t1, int t2)
{
	long long int a1, b1, c1, a2, b2, c2;

	a1 = a[t1][3] - a[t1][1], b1 = a[t1][0] - a[t1][2], c1 = (a[t1][3] - a[t1][1]) * a[t1][0] - (a[t1][2] - a[t1][0]) * a[t1][1];
	a2 = a[t2][3] - a[t2][1], b2 = a[t2][0] - a[t2][2], c2 = (a[t2][3] - a[t2][1]) * a[t2][0] - (a[t2][2] - a[t2][0]) * a[t2][1];
	if (a1 * b2 - b1 * a2 == 0)
	{
		if (a1 * c2 - a2 * c1 == 0 && b1 * c2 - b2 * c1 == 0) // overlapping lines
		{
			long long dx1, dy1, dx2, dy2;
			long long ix, iy;

			dx1 = a[t1][2] - a[t1][0], dy1 = a[t1][3] - a[t1][1], dx2 = a[t2][2] - a[t2][0], dy2 = a[t2][3] - a[t2][1];
			if (dx1 * dx2 >= 0 && dy1 * dy2 >= 0) //same direction
			{
				ix = a[t2][0] - a[t1][0], iy = a[t2][1] - a[t1][1];
				if (ix * dx1 >= 0 && iy * dy1 >= 0)
					d[t1][t2] = sqrt((double)(ix * ix + iy * iy)), d[t2][t1] = 0.0, check[t2][t1] = true;
				else
					d[t2][t1] = sqrt((double)(ix * ix + iy * iy)), d[t1][t2] = 0.0, check[t1][t2] = true;
			}
			else //opposite direction
			{
				ix = a[t2][0] - a[t1][0], iy = a[t2][1] - a[t1][1];
				if (dx1 * ix >= 0 && dy1 * iy >= 0) //intersect in middle
					d[t1][t2] = d[t2][t1] = sqrt((double)(ix * ix + iy * iy)) / 2;
				else
					check[t1][t2] = check[t2][t1] = true;
			}
		}
		else
			check[t1][t2] = check[t2][t1] = true;
	}
	else
	{
		long long int xs, xm, ys, ym;
		double x, y;
		xs = b2 * c1 - b1 * c2, xm = a1 * b2 - a2 * b1;
		ys = a1 * c2 - a2 * c1, ym = a1 * b2 - a2 * b1;
		x = (double)xs / (double)xm;
		y = (double)ys / (double)ym;
		if (0.0 <= x && x <= (double)l && 0.0 <= y && y <= (double)l) // intersection in l square
		{
			double dx1, dy1, dx2, dy2, ix1, iy1, ix2, iy2;
			dx1 = (double)(a[t1][2] - a[t1][0]), dy1 = (double)(a[t1][3] - a[t1][1]), dx2 = (double)(a[t2][2] - a[t2][0]), dy2 = (double)(a[t2][3] - a[t2][1]);
			ix1 = x - (double)a[t1][0], iy1 = y - (double)a[t1][1], ix2 = x - (double)a[t2][0], iy2 = y - (double)a[t2][1];
			if (!(dx1 * ix1 >= 0.0 && dy1 * iy1 >= 0.0 && dx2 * ix2 >= 0.0 && dy2 * iy2 >= 0.0)) //intersection exists but...
				check[t1][t2] = check[t2][t1] = true;
			else
			{
				double d1, d2;
				d1 = sqrt(ix1 * ix1 + iy1 * iy1), d2 = sqrt(ix2 * ix2 + iy2 * iy2);
				if (t2 > n - 4)
					d[t1][t2] = d1, check[t2][t1]=true;
				else
				{
					d[t1][t2] = d1, d[t2][t1] = d2;
					if (d1 > d2)
						check[t2][t1] = true;
					else if (d1 < d2)
						check[t1][t2] = true;
				}
			}
		}
		else
			check[t1][t2] = check[t2][t1] = true;
	}

	ppair temp;
	if (!check[t1][t2])
	{
		temp = ppair(d[t1][t2], pair<int, int>(t1, t2));
		q.push(temp);
	}
	if (!check[t2][t1])
	{
		temp = ppair(d[t2][t1], pair<int, int>(t2, t1));
		q.push(temp);
	}
}

int main()
{
	int i, j;
	scanf("%d %lld ", &n, &l);
	for (i = 1; i <= n; i++)
		for (j = 0; j < 4; j++)
			scanf("%lld ", &a[i][j]);
	a[++n][0] = 0, a[n][1] = 0, a[n][2] = l, a[n][3] = 0;
	a[++n][0] = l, a[n][1] = 0, a[n][2] = l, a[n][3] = l;
	a[++n][0] = 0, a[n][1] = l, a[n][2] = l, a[n][3] = l;
	a[++n][0] = 0, a[n][1] = 0, a[n][2] = 0, a[n][3] = l;

	for (i = 1; i <= n - 4; i++)
		for (j = i + 1; j <= n; j++)
			cross_check(i, j);

	int k, idx, temp;
	double mini;
	for (k = 1; k <= n - 4; k++)
	{
		while (check[q.top().second.first][q.top().second.second])
			q.pop();
		mini = q.top().first, idx=q.top().second.first;
		for (i = 1; i <= n; i++)
		{
			check[idx][i] = true;
			if (d[idx][i] > mini)
				check[i][idx] = true;
		}
	}
	temp = (int)(mini * 100 + 0.5);
	printf("%.2lf", (double)temp / 100);
	return 0;
}