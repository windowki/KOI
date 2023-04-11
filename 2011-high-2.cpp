#include <iostream>
#include <vector>
#include <memory.h>
#include <bitset>

using namespace std;
int n, m;
int front, rear, queue[10001];
int n_group, group_size[10001], group[10001];
vector<int> adj[10001], adj_[10001];
vector<pair<int, int>> edge_;
int level[10001];
vector<pair<int, int>> n_AB;

int group_node(int root)
{
	int i, parent, son;

	front = rear = 0;
	queue[++rear] = root, group[root] = n_group;
	do {
		parent = queue[++front];
		for (i = 0; i < adj[parent].size(); i++)
		{
			son = adj[parent][i];
			if (!group[son])
				queue[++rear] = son, group[son] = n_group;
		}
	} while (front != rear);
	return rear;
}

pair<int, int> check_bipartite(int g)
{
	int i, parent, son;
	int n_odd = 0, n_even = 0;
	front = rear = 0;
	queue[++rear] = g, level[g] = 1;
	do {
		parent = queue[++front];
		if (level[parent] % 2)
			n_odd += group_size[parent];
		else
			n_even += group_size[parent];

		for (i = 0; i < adj_[parent].size(); i++)
		{
			son = adj_[parent][i];
			if (!level[son])
				queue[++rear] = son, level[son] = level[parent] + 1;
			else if (level[parent] == level[son]) // not bipartite graph
				return pair<int, int>(-1, -1);
		}
	} while (front != rear);
	return pair<int, int>(n_odd, n_even);
}

int main()
{
	int test = 5;
	int i, mode, u, v;
	while (test--)
	{
		cin >> n >> m;
		for (i = 1; i <= m; i++)
		{
			cin >> mode >> u >> v;
			if (mode == 1)
				adj[u].push_back(v), adj[v].push_back(u);
			else
				edge_.push_back(make_pair(u, v));
		}

		//group over friend edges
		memset(group, 0, sizeof(group)), n_group = 0;
		for (i = 1; i <= n; i++)
			if (!group[i])
			{
				n_group++;
				group_size[n_group] = group_node(i);
			}

		// make adjacency list of the groups
		for (auto& p : edge_)
		{
			u = group[p.first], v = group[p.second];
			adj_[u].push_back(v), adj_[v].push_back(u);
		}

		//check if bipartite graph (no self edge)
		bool unable = false;
		memset(level, 0, sizeof(level));
		for (i = 1; i <= n_group; i++)
			if (!level[i])
			{
				pair<int, int> p = check_bipartite(i);
				if (p.first == -1)
				{
					unable = true;
					break;
				}
				n_AB.push_back(p);
			}

		if (unable)
			cout << -1 << endl;
		else
		{
			bitset<5001> a = 1, left, right;
			for (auto p : n_AB)
			{
				left = a << p.first;
				right = a << p.second;
				a = left|right;
			}
			for (i = n / 2; i >= 0; i--)
				if (a[i])
				{
					cout << n - 2 * i << endl;
					break;
				}
		}
		n_AB.clear();

		// clear vectors
		edge_.clear();
		for (i = 1; i <= n; i++)
			adj[i].clear();
		for (i = 1; i <= n_group; i++)
			adj_[i].clear();
	}
	return 0;
}
