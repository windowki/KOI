#include <iostream>
#include <string>

using namespace std;
string seq, bridge[2];
int n, d[21][2][102], seq_n;

int main()
{
	int i, j, k, l;

	getline(cin, seq);
	seq_n = seq.length();
	getline(cin, bridge[0]);
	getline(cin, bridge[1]);
	n = bridge[0].length();
	
	for (i = 0; i <= 1; i++)
		for (j = 0; j < n; j++)
			d[0][i][j] = (seq[0] == bridge[i][j]);

	for (l = 1; l < seq_n; l++)
		for (i = 0; i <= 1; i++)
			for (j = 0; j < n; j++)
				for (k = 0; k < j; k++)
					if (bridge[i][j] == seq[l])
						d[l][i][j] += d[l-1][1-i][k];
	
	int sum = 0;
	for (i = 0; i <= 1; i++)
		for (j = 0; j < n; j++)
			sum += d[seq_n - 1][i][j];
	printf("%d", sum);
	return 0;
}