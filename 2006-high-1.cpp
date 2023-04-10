#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <algorithm>
#define INF 99999999
#define MX2(x,y) x>y ? x:y

using namespace std;
int n, d[10005];
pair<int, int> a[10005];

int main()
{
	int i, j, mx, temp;
	scanf("%d ", &n);
	for (i = 1; i <= n; i++)
	{
		scanf("%d %d ", &a[i].first, &a[i].second), d[i] = INF;
		if (a[i].second < 0)
			a[i].second *= -1;
	}
	sort(a + 1, a + n + 1);
	
	for (i = 1; i <= n; i++)
	{
		mx = 0;
		for (j = i-1; j >= 0; j--)
		{
			if (mx < a[j + 1].second)
				mx = a[j + 1].second;
			temp = MX2(a[i].first - a[j + 1].first, mx * 2);
			if (d[i] > d[j] + temp)
				d[i] = d[j] + temp;
		}
	}
	printf("%d", d[n]);
	return 0;
}