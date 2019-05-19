#include <iostream>
#include <list>
#include <queue>

std::list<int> arr[100];

void BFS(int start) {
	bool visited[100] = { false };
	std::queue<int> q;
	q.push(start);
	while (!q.empty()) {
		int temp = q.front();
		std::cout << temp << " ";
		q.pop();
		visited[temp] = true;
		for (auto v : arr[temp]) {
			if (!visited[v]) {
				q.push(v);
			}
		}
	}
}

int main() {
	int N, M;
	std::cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int from, to;
		std::cin >> from >> to;
		arr[from].push_back(to);
		arr[to].push_back(from);
	}
	int start;
	std::cin >> start;
	BFS(start);
	system("pause");
	return 0;
}
