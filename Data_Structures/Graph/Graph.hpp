#pragma once

#ifndef GRAPH_HEADER
#define GRAPH

#include <unordered_map>
#include <queue>

template<typename NodeType, typename EdgeType>
class Graph {
	public:
		typedef NodeType node;
		typedef EdgeType edge;
		typedef std::unordered_map<node, edge> Edges;
		typedef std::unordered_map<node, Edges> NodeMap;

		typedef typename NodeMap::iterator node_iter;
		typedef typename Edges::iterator edges_iter;
	private:
		NodeMap graph;
		int nodesCount = 0;
		int edgesCount = 0;

	public:
		Graph() = default;
		Graph(const Graph& other) = delete;
		Graph& operator=(const Graph& rhs) = delete;
		~Graph() = default;

		bool addNode(const node& n) {
			node_iter it = graph.find(n);
			if (it == graph.end()) {
				graph.insert(std::make_pair(n, Edges()));
				nodesCount++;
				return true;
			}
			
			return false;
		}

		bool addEdge(const node& from, const node& to, const edge& e) {
			node_iter from_it = graph.find(from);
			if (from_it == graph.end()) {
				return false;
			}

			node_iter to_it = graph.find(to);
			if (to_it == graph.end()) {
				return false;
			}
			
			// graph[from][to] = e; It is valid
			// it_from->second[to] = e; Also valid
			Edges& adjacent = from_it->second;
			adjacent[to] = e;
			edgesCount++;
			return true;
		}

		bool removeNode(const node& n) {
			node_iter node_it = graph.find(n);
			if (node_it == graph.end()) {
				return false;
			}
			graph.erase(n);
			nodesCount--;
			int removedEdges = node_it->second.size();
			for (node_it = graph.begin(); node_it != graph.end(); node_it++) {
				Edges& adjacent = node_it->second;
				edges_iter it = adjacent.find(n);
				if (it != adjacent.end()) {
					adjacent.erase(n);
					removedEdges++;
				}
			}
			edgesCount -= removedEdges;
			return true;
		}

		bool removeEdge(const node& from, const node& to) {
			node_iter from_it = graph.find(from);
			if (from_it == graph.end()) {
				return false;
			}
			node_iter to_it = graph.find(to);
			if (to_it == graph.end()) {
				return false;
			}
			Edges& adjacent = from_it->second;
			if (adjacent.erase(to) != 0) {
				edgesCount--;
				return true;
			}
			return false;
		}

		bool BFS(const node& start) {
			node_iter start_it = graph.find(start);
			if (start_it == graph.end()) {
				return false;
			}

			std::unordered_map<node, bool> visited;
			for (node_iter it = graph.begin(); it != graph.end(); it++) {
				const node& n = it->first;
				visited[n] = false;
			}

			std::queue<node> queue;
			queue.push(start);
			visited[start] = true;
			while (!queue.empty()) {
				node n = queue.front();
				queue.pop();
				std::cout << n << std::endl;
				node_iter node_it = graph.find(n);
				Edges& neighbours = node_it->second;
				for (edges_iter it = neighbours.begin(); it != neighbours.end(); it++) {
					const node &to = it->first;
					if (!visited[to]) {
						queue.push(to);
						visited[to] = true;
					}
				}
			}
			return true;
		}
};
#endif // !GRAPH_HEADER
