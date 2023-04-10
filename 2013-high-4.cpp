#include <iostream>
#include <algorithm>

using namespace std;
int n, k, rightmost;
int p, seg[524288], argmin;
pair<pair<int, int>, int> a[150001];
pair<int, int> tree[150001];
long long weight[150001];
int path[150001];
long long g[150001], n_path;
bool visit[150001];

void find_argmin(int target_low, int target_up, int low, int up, int root)
{
    if (target_low <= low && up <= target_up)
        argmin = (a[argmin].second > a[seg[root]].second ? seg[root] : argmin);
    else if (!(up < target_low || target_up < low)) // if partially overlap
    {
        find_argmin(target_low, target_up, low, (low + up) / 2, root * 2);
        find_argmin(target_low, target_up, (low + up) / 2 + 1, up, root * 2 + 1);
    }
}

int make_tree(int left, int right)
{
    if (left > right)
        return 0;
    argmin = 0;
    find_argmin(left, right, 1, p, 1);
    int root = argmin;
    tree[root].first = make_tree(left, root - 1);
    tree[root].second = make_tree(root + 1, right);
    return root;
}

void find_weight(int root, int left, int right, int y)
{
    weight[root] = (long long)(right - left) * (a[root].second - y);
    int lchild = tree[root].first;
    int rchild = tree[root].second;
    if (lchild)
        find_weight(lchild, left, a[root].first.first, a[root].second);
    if (rchild)
        find_weight(rchild, a[root].first.second, right, a[root].second);

    if (weight[lchild] >= weight[rchild])
        weight[root] += weight[lchild], path[root] = lchild;
    else
        weight[root] += weight[rchild], path[root] = rchild;
}

void dfs(int root)
{
    if (!visit[root])
    {
        visit[root] = true;
        g[++n_path] = weight[root];
    }
    visit[path[root]] = true;
    int lchild = tree[root].first;
    int rchild = tree[root].second;
    if (lchild)
        dfs(lchild);
    if (rchild)
        dfs(rchild);
}

int main()
{
    int i, x, y;
    cin >> n;
    cin >> x >> y;
    n = n / 2 - 1;
    for (i = 1; i <= n; i++)
        cin >> a[i].first.first >> a[i].second >> a[i].first.second >> y;
    cin >> rightmost >> y;
    cin >> k;

    // construct segment tree to find argmin of a[].second
    p = 1;
    while (p < n)
        p *= 2;
    for (i = p; i < p + n; i++)
        seg[i] = i - p + 1;
    a[0].second = 1000000001;
    for (i = p - 1; i >= 1; i--)
        seg[i] = (a[seg[i * 2]].second < a[seg[i * 2 + 1]].second ? seg[i * 2] : seg[i * 2 + 1]);

    // construct binary tree for horizontal lines
    int root = make_tree(1, n);
    // find weight of each node
    find_weight(root, 0, rightmost, 0);
    // greedy to find optimal solution
    dfs(root);
    sort(g + 1, g + n_path + 1, greater<long long>());
    long long answer = 0;
    for (i = 1; i <= k && i <= n_path; i++)
        answer += g[i];
    cout << answer;
    return 0;
}