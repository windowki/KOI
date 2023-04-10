#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <memory.h>

int b[3], d[501][501];

void process(int k1, int k2)
{
	int i, j, k, check;
	memset(d, 0, sizeof(d));
	//1 for 'A', 2 for 'B'
	for (i = 0; i <= k1; i++)
		for (j = 0; j <= k2; j++)
		{
			check = 1;
			for (k = 0; k < 3; k++)
			{
				if (i - b[k] >= 0)
					check *= d[i - b[k]][j];
				if (j - b[k] >= 0)
					check *= d[i][j - b[k]];
			}
			if (check == 1)
				d[i][j] = 2;
			else
				d[i][j] = 1;
		}
	printf("%c\n", (d[k1][k2] == 1 ? 'A' : 'B'));
}

int main()
{
	int i, k1, k2;
	for (i = 0; i < 3; i++)
		scanf("%d ", &b[i]);
	for (i = 1; i <= 5; i++)
	{
		scanf("%d %d", &k1, &k2);
		process(k1, k2);
	}
	return 0;
}