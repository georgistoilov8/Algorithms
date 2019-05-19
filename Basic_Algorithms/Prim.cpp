#include <iostream>
#include <list>
#include <queue>

struct Edges {
	int vertex;
	int weight;
	bool operator<(const Edges& edge) const {
		return weight > edge.weight;
	}
};

std::list<Edges> arr[100];
int parent[100];

void Prim(int N, int start) {
	std::priority_queue<Edges> q;
	bool ready[100] = { false };
	int weights[100];
	for (int i = 0; i < N; i++) {
		weights[i] = 100000000;
	}
	q.push(Edges{ start, 0 });
	weights[start] = 0;
	while (!q.empty()) {
		Edges current = q.top();
		q.pop();
		ready[current.vertex] = true;
		for (auto v : arr[current.vertex]) {
			if (!ready[v.vertex]) {
				if (weights[v.vertex] > v.weight) {
					weights[v.vertex] = v.weight;
					parent[v.vertex] = current.vertex;
				}
				q.push(Edges{v.vertex, v.weight});
			}
		}
	}
}

int main() {
	int N, M;
	std::cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int from, to, weight;
		std::cin >> from >> to >> weight;
		arr[from].push_back(Edges{ to, weight });
		arr[to].push_back(Edges{ from, weight });

	}
	int start;
	std::cin >> start;
	Prim(N, start);
	for (int i = 0; i < N; i++) {
		if (i != start) {
			printf("%d - %d \t\n", parent[i], i);
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
