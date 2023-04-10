#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int n;
int cnt, order[1001], level[1001], range[1001][2];
struct data {
	int left, right;
} s[1001];

void inorder(int v)
{
	if (v != -1)
	{
		inorder(s[v].left);
		order[++cnt] = v;
		inorder(s[v].right);
	}
}

void levelorder()
{
	int front = 0, rear = 0, v, left, right;
	int queue[3005];
	queue[++rear] = level[1] = 1;
	do {
		v = queue[++front];
		left = s[v].left, right= s[v].right;
		if (left != -1)
			queue[++rear] = left, level[left] = level[v] + 1;
		if (right != -1)
			queue[++rear] = right, level[right] = level[v] + 1;
	} while (front != rear);
}

int main()
{
	int i, v;
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		scanf("%d ", &v);
		scanf("%d %d ", &s[v].left, &s[v].right);
	}

	inorder(1);
	levelorder();
	
	for (i = 1; i <= n; i++)
	{
		v = order[i];
		if (range[level[v]][0] == 0)
			range[level[v]][0] = i;
		range[level[v]][1] = i;
	}

	int max = 0, argumax = 0;
	for (i = 1; i <= n; i++)
		if (max < range[i][1] - range[i][0] + 1)
			max = range[i][1] - range[i][0] + 1, argumax = i;

	printf("%d %d", argumax, max);
	return 0;
}