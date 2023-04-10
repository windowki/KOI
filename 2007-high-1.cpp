#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int a, b, d, sgn;

int main()
{
	int i, t1, t2, td, tsgn;

	scanf("%d %d", &a, &b), d=b-a;
	
	if (d > 0)
		sgn = 1;
	else if (d < 0)
		sgn = -1, d*=-1;
	else
		sgn = 0;
	while (d % 2 == 0 && d)
		d /= 2;

	for (i = 1; i <= 5; i++)
	{
		scanf("%d %d", &t1, &t2), td=t2-t1;

		if (td > 0)
			tsgn = 1;
		else if (td < 0)
			tsgn = -1, td *= -1;
		else
			tsgn = 0;

		if (sgn == 0)
		{
			if (tsgn == 0)
				printf("Y\n");
			else
				printf("N\n");;
		}
		else if (sgn && sgn == tsgn)
		{
			if (td % d == 0)
				printf("Y\n");
			else
				printf("N\n");
		}
		else
			printf("N\n");
	}
	return 0;
}