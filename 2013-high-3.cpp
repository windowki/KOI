#include <iostream>
#include <algorithm>

using namespace std;
long long n, a[100001], grad;
pair<double, int> ratio[100001];

long long distance(int k)
{
    long long i, dist = 0;
    for (i = 0; i < n; i++)
        dist += abs(a[i] - i * k);
    return dist;
}

int main()
{
    int i;
    cin >> n;
    for (i = 0; i < n; i++)
    {
        cin >> a[i];
        if (i)
            ratio[i] = make_pair((double)a[i] / i, i);
    }
    sort(ratio + 1, ratio + n);

    long long dist_left, dist_right;
    if (n == 1)
    {
        cout << 0;
        return 0;
    }
    grad = -n * (n - 1) / 2;
    for (i = 1; i < n; i++)
    {
        // gradient when k >= ratio[i].first
        grad += ratio[i].second * 2;
        if (grad >= 0)
        {
            dist_left = distance((int)ratio[i].first);
            dist_right = distance((int)ratio[i].first + 1);
            cout << (dist_left < dist_right ? dist_left : dist_right);
            break;
        }
    }
    return 0;
}