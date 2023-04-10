#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int a[7][4], able;

void process(int t1, int t2)
{
	if (t1 == 6)
	{
		int i, j;
		able = 1;
		for (i = 1; i <= 6; i++)
			for (j = 1; j <= 3; j++)
				if (a[i][j])
					able = 0;
	}
	else
	{
		if (a[t1][1] > 0 && a[t2][3] > 0)
		{
			a[t1][1]--, a[t2][3]--;
			if (t2 == 6)
				process(t1 + 1, t1 + 2);
			else
				process(t1, t2 + 1);
			a[t1][1]++, a[t2][3]++;
		}
		if (a[t1][2] > 0 && a[t2][2] > 0)
		{
			a[t1][2]--, a[t2][2]--;
			if (t2 == 6)
				process(t1 + 1, t1 + 2);
			else
				process(t1, t2 + 1);
			a[t1][2]++, a[t2][2]++;
		}
		if (a[t1][3] > 0 && a[t2][1] > 0)
		{
			a[t1][3]--, a[t2][1]--;
			if (t2 == 6)
				process(t1 + 1, t1 + 2);
			else
				process(t1, t2 + 1);
			a[t1][3]++, a[t2][1]++;
		}
	}
}

int main()
{
	int k, i, j;
	for (k = 1; k <= 4; k++)
	{
		able = 0;
		for (i = 1; i <= 6; i++)
			for (j = 1; j <= 3; j++)
				scanf("%d ", &a[i][j]);
		process(1,2);
		printf("%d\n", able);
	}
	return 0;
}