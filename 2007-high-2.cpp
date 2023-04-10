#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <algorithm>
#define K 20070713

using namespace std;
pair<int, int> a[100055];
int n, ad[100055], d[100055];
int num;

int bi_search(int s, int e)
{
	int mid;
	while (s <= e)
	{
		mid = (s + e) / 2;
		if (a[mid].first <= num && num < a[mid + 1].first)
			return mid;

		if (a[mid].first <= num)
			s = mid + 1;
		else
			e = mid - 1;
	}
	return mid;
}

void process(void)
{
	int i;
	d[n + 1] = 1;
	for (i = n; i >= 1; i--)
	{
		if (a[i].second < a[i + 1].first) //new group in current situation
			d[i] = (2 * d[i + 1]) % K;
		else
			d[i] = (d[ad[i] + 1] + d[i + 1]) % K;
	}
}

int main()
{
	int i;

	scanf("%d", &n);
	for (i = 1; i <= n; i++)
		scanf("%d %d", &a[i].first, &a[i].second);
	sort(a + 1, a + n + 1);
	a[n + 1].first = 999999999;
	for (i = 1; i <= n; i++)
	{
		num = a[i].second;
		ad[i] = bi_search(i, n);
	}
	process();
	printf("%d", d[1]);
	return 0;
}