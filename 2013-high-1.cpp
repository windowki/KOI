#include <iostream>
#include <algorithm>

using namespace std;
int m, n, l;
int s[100001];
pair<int, int> a[100001];

int find_low(int left, int right, int key)
{
    int mid;
    while (left <= right)
    {
        mid = (left + right) / 2;
        if (key == s[mid])
            return mid;
        if (key < s[mid])
            right = mid - 1;
        else
            left = mid + 1;
    }
    return left;
}

int find_up(int left, int right, int key)
{
    int mid;
    while (left <= right)
    {
        mid = (left + right) / 2;
        if (key == s[mid])
            return mid;
        if (key < s[mid])
            right = mid - 1;
        else
            left = mid + 1;
    }
    return right;
}

int main()
{
    int i;
    cin >> m >> n >> l;
    for (i = 1; i <= m; i++)
        cin >> s[i];
    for (i = 1; i <= n; i++)
        cin >> a[i].first >> a[i].second;
    sort(s + 1, s + m + 1);

    int count = 0, idx_low, idx_up;
    for (i = 1; i <= n; i++)
    {
        if (a[i].second > l)
            continue;
        idx_low = find_low(1, m, a[i].first - (l - a[i].second)); // find the smallest idx s.t. s[idx]>=key
        idx_up = find_up(1, m, a[i].first + (l - a[i].second));   // find the biggest idx s.t. s[idx]<=key'
        count += (idx_low <= idx_up);
    }
    cout << count;
    return 0;
}