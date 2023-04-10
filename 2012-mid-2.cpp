#include <iostream>
#include <algorithm>
#define MAX2(x, y) (x > y ? x : y)

using namespace std;
int n, s, d[300001][2];
pair<int, int> a[300001];

int bin_search(int left, int right, int key)
{
    int mid;
    while (left <= right)
    {
        mid = (left + right) / 2;
        if (key == a[mid].first)
            return mid;
        if (key < a[mid].first)
            right = mid - 1;
        if (key > a[mid].first)
            left = mid + 1;
    }
    return right;
}

int main()
{
    int i, idx = 0, prev;
    cin >> n >> s;
    for (i = 1; i <= n; i++)
        cin >> a[i].first >> a[i].second;
    sort(a + 1, a + n + 1);
    // remove redundant paints
    for (i = 1; i <= n; i++)
    {
        idx += (a[i].first != a[i - 1].first);
        a[idx].first = a[i].first, a[idx].second = a[i].second;
    }
    n = idx;

    for (i = 1; i <= n; i++)
    {
        d[i][0] = MAX2(d[i - 1][0], d[i - 1][1]);
        // find maximum idx s.t. a[idx].first <= a[i].first-s
        prev = bin_search(0, i - 1, a[i].first - s);
        if (prev >= 0)
            d[i][1] = MAX2(d[prev][0], d[prev][1]) + a[i].second;
    }
    cout << MAX2(d[n][0], d[n][1]);
    return 0;
}
