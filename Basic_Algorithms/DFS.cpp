#include <iostream>
#include <list>
#include <stack>

std::list<int> arr[100];

void DFS(int start) {
	bool visited[100] = { false };
	std::stack<int> q;
	q.push(start);
	while (!q.empty()) {
		int temp = q.top();
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
	DFS(start);
	system("pause");
	return 0;
}

/*
Test:
12 11
1 2
1 7
1 8
2 3
2 6
8 9
8 12
3 4
3 5
9 10
9 11
*/
