#include <iostream>
#include <algorithm>

using namespace std;
int n, a[10001], budget, upper;

int main()
{
    int i;
    cin >> n;
    for (i = 1; i <= n; i++)
        cin >> a[i];
    cin >> budget;
    sort(a + 1, a + n + 1);

    int new_sum;
    for (i = 1; i <= n; i++)
    {
        new_sum = (a[i] - a[i - 1]) * (n - i + 1);
        if (budget < new_sum)
        {
            upper += budget / (n - i + 1);
            break;
        }
        budget -= new_sum;
        upper += a[i] - a[i - 1];
    }
    cout << upper;
    return 0;
}