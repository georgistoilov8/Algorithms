#include <iostream>
#include <algorithm>

struct Edges {
	int source;
	int destination;
	int weight;
	bool operator<(const Edges& edge) const {
		return weight < edge.weight;
	}
};

Edges arr[100];

struct DisjointSet {
	int n;
	int parent[100];
	int rank[100];

	DisjointSet(int n_) {
		n = n_;
		for (int i = 0; i < n; i++) {
			parent[i] = i;
			rank[i] = 0;
		}
	}

	int find(int x) {
		if (parent[x] != x) {
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}

	void unite(int x, int y) {
		int fx = find(x);
		int fy = find(y);
		if (rank[fx] < rank[fy]) {
			parent[fx] = y;
		}
		else {
			parent[fy] = x;
		}

		if (rank[fx] == rank[fy]) {
			rank[fx]++;
		}
	}
};

int main() {
	int N, M;
	std::cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int from, to, weight;
		std::cin >> from >> to >> weight;
		arr[i] = Edges{from, to, weight };
	}
	DisjointSet ds(N);
	std::sort(arr, arr + M);
	for (int i = 0; i < M; i++) {
		if (ds.find(arr[i].source) != ds.find(arr[i].destination)) {
			ds.unite(arr[i].source, arr[i].destination);
			std::cout << arr[i].source << " <-> " << arr[i].destination << std::endl;
		}
	}
	system("pause");
	return 0;
}

/*
Test:
9 14
0 1 4
0 7 8
1 7 11
1 2 8
7 8 7
7 6 1
2 8 2
8 6 6
2 3 7
2 5 4
6 5 2
3 4 9
3 5 14
5 4 10
*/
