#include <iostream>
#include <algorithm>
#define MAX2(x, y) (x > y ? x : y)

using namespace std;
int n, l;
pair<int, int> rods[100001];
int list_up[100001], list_low[100001], len_up, len_low;
long long d[100001][2];

int find_idx(int key, int mode)
{
    int left, right, mid;
    if (mode == 0)
    {
        left = 1, right = len_up;
        while (left <= right)
        {
            mid = (left + right) / 2;
            if (key == list_up[mid])
                return mid;
            if (key < list_up[mid])
                right = mid - 1;
            else
                left = mid + 1;
        }
    }
    else
    {
        left = 1, right = len_low;
        while (left <= right)
        {
            mid = (left + right) / 2;
            if (key == list_low[mid])
                return mid;
            if (key < list_low[mid])
                right = mid - 1;
            else
                left = mid + 1;
        }
    }
}

int main()
{
    int i, j;
    cin >> n >> l;
    for (i = 1; i <= n; i++)
    {
        cin >> rods[i].first >> rods[i].second;
        list_up[i] = rods[i].first, list_low[i] = rods[i].second;
    }
    sort(rods + 1, rods + n + 1);
    sort(list_up + 1, list_up + n + 1);
    sort(list_low + 1, list_low + n + 1);
    for (i = 1; i <= n; i++)
    {
        if (list_up[i] != list_up[i - 1] || i == 1)
            list_up[++len_up] = list_up[i];
        if (list_low[i] != list_low[i - 1] || i == 1)
            list_low[++len_low] = list_low[i];
    }

    int idx_upper, idx_lower;
    long long delta, mem_up, mem_low;
    for (i = 1; i <= n; i++)
    {
        delta = abs(rods[i].first - rods[i].second) + l;
        idx_upper = find_idx(rods[i].first, 0);
        idx_lower = find_idx(rods[i].second, 1);

        mem_up = MAX2(d[idx_upper][0], d[idx_lower][1] + delta);
        mem_low = MAX2(d[idx_lower][1], d[idx_upper][0] + delta);
        d[idx_upper][0] = mem_up;
        d[idx_lower][1] = mem_low;
    }

    long long opt = 0;
    for (i = 1; i <= len_up; i++)
        opt = MAX2(opt, d[i][0]);
    for (i = 1; i <= len_low; i++)
        opt = MAX2(opt, d[i][1]);
    cout << opt;
    return 0;
}