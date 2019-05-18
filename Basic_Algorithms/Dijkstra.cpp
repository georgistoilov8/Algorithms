#include <iostream>
#include <list>

# define SIZE 100001
# define MAX_INT 1000000000
struct GraphElement {
	int vertex;
	int price;
	int time;
};

std::list<GraphElement> graph[SIZE];

void Dijkstra(int N) {
	bool ready[SIZE] = { false };
	int distance[SIZE] = { false };
	for (int i = 0; i <= N; i++) {
		distance[i] = MAX_INT;
	}
	distance[1] = 0;
	while (!ready[N]) {
		int current = 1;
		int min = MAX_INT;
		while (ready[current]) {
			current++;
		}
		for (int i = 1; i <= N; i++) {
			if (distance[i] < min && !ready[i]) {
				min = distance[i];
				current = i;
			}
		}

		ready[current] = true;
		for (auto edge : graph[current]) {
			if (!ready[edge.vertex]) {
				int new_distance = distance[current] + edge.time;
				if (new_distance < distance[edge.vertex]) {
					distance[edge.vertex] = new_distance;
				}
			}
		}
	}
	std::cout << distance[N] << std::endl;
}

int main() {
	int crossroads, tunnels, time;
	std::cin >> crossroads >> tunnels >> time;

	for (int i = 0; i < tunnels; i++) {
		int from, to, neededTime, price;
		std::cin >> from >> to >> price >> neededTime;
		graph[from].push_back(GraphElement{ to,price,neededTime });
	}

	Dijkstra(crossroads);
	system("pause");
	return 0;
}
