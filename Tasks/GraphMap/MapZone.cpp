#include "MapZone.h"

MapZone::MapZone(){}

MapZone::~MapZone(){}

/*
	If node exist, then do nothing, else insert it.
*/
bool MapZone::addNode(const std::string& node) {
	NodesIterator it = graph.find(node);
	if (it == graph.end()) {
		graph.insert(std::make_pair(node, Edges()));
		return true;
	}
	return false;
}

/*
	If "from" or "to" are not nodes in the graph,
	then we can't put edge between them. Else add
	edge.
*/
bool MapZone::addEdge(const std::string& from, const std::string& to, const std::string& edge) {
	NodesIterator fromIt = graph.find(from);
	if (fromIt == graph.end()) {
		return false;
	}

	if (graph.find(to) == graph.end()) {
		return false;
	}

	fromIt->second[to] = edge;
	return true;
}

/*
	Breadth-first search using std::queue.
	Traverse all the zones and write into file the following information:
		1. All of the connection between the zones.
		Example: A -> B;
				 B -> C;
				 C -> B;
		2. Mark all the zones that can't be reached.
*/
bool MapZone::BFS_traverse(const std::string& start, std::string& nextNode, Set& collectedKeys, Set& alreadyVisitedNodes, std::fstream& file) {
	NodesIterator startIt = graph.find(start);
	if (startIt == graph.end()) {
		return false;
	}

	std::unordered_map<std::string, bool> visited;
	for (NodesIterator it = graph.begin(); it != graph.end(); it++) {
		visited[it->first] = false;
	}

	std::queue<VisitData> queue;
	visited[start] = true;
	queue.push(VisitData(nullptr, &start, nullptr));

	while (!queue.empty()) {
		VisitData current = queue.front();
		queue.pop();
		// It can be without printGraphNodes, but why not.
		if (current.from && !printGraphNodes(*current.from, *current.edge, *current.to)) {
			return true;
		}

		const std::string& from = *current.to;
		visited[from] = true;

		for (Set::iterator it = keys[from].begin(); it != keys[from].end(); it++) {
			if (*it != "") {
				/* Optimization was done here!
				bool isCollected = false;
				for (Vector::iterator collectedKeysIt = collectedKeys.begin(); collectedKeysIt != collectedKeys.end(); collectedKeysIt++) {
					if (*collectedKeysIt == *it) {
						isCollected = true;
						break;
					}
				}
				if (!isCollected) {
					collectedKeys.push_back(*it);
				}
				*/
				bool b = true;
				if (collectedKeys.find(*it) == collectedKeys.end()) {
					b = false;
					collectedKeys.insert(*it);
				}
				nextNode = from;
				if (!b) {
					BFS_traverse(nextNode, nextNode, collectedKeys, alreadyVisitedNodes, file);
				}
			}
		}	

		Edges& adj = graph[*current.to];
		for (EdgesIterator it = adj.begin(); it != adj.end(); it++) {
			const std::string& to_node = it->first;

			if (alreadyVisitedNodes.find(from) == alreadyVisitedNodes.end()) {
				file << from;
				file << " -> ";
				file << to_node;
				file << "[label=\"";
				file << it->second;
				file << "\"];\n";
			}
			
			if (!visited[to_node]) {
				bool shouldVisit = false;
				if (it->second != "") {
					/*	Optimization was done here!
					for (Vector::const_iterator cIt = collectedKeys.begin(); cIt != collectedKeys.end(); cIt++) {
						if (it->second == *cIt) {
							shouldVisit = true;
							break;
						}
					}
					*/
					if (collectedKeys.find(it->second) != collectedKeys.end()) {
						shouldVisit = true;
					}
				}
				else {
					shouldVisit = true;
				}
				
				if (shouldVisit) {
					visited[to_node] = true;
					queue.push(VisitData(&from, &to_node, &(it->second)));
				}
			}
		}
		alreadyVisitedNodes.insert(from);
	}

	/*	If you want for every traverse to print the unreached nodes, uncomment.
		std::cout << "Unreached nodes:\n";
		for (NodesIterator it = graph.begin(); it != graph.end(); it++) {
			if (!visited[it->first]) {
				std::cout << it->first << std::endl;	
			}
		}
	*/
	for (NodesIterator it = graph.begin(); it != graph.end(); it++) {
		if (!visited[it->first]) {
			Edges& adj = graph[it->first];

			for (EdgesIterator edgeIt = adj.begin(); edgeIt != adj.end(); edgeIt++) {
				const std::string& to_node = edgeIt->first;
				if (alreadyVisitedNodes.find(it->first) == alreadyVisitedNodes.end()) {
					file << it->first;
					file << " -> ";
					file << to_node;
					file << "[label=\"";
					file << edgeIt->second;
					file << "\"];\n";
				}
			}
			if (alreadyVisitedNodes.find(it->first) == alreadyVisitedNodes.end()) {
				file << it->first;
				file << "[color=red,style=filled, fillcolor=\"#ffefef\"];\n";
			}
			alreadyVisitedNodes.insert(it->first);
		}
	}
	return true;
}

bool MapZone::printGraphNodes(const std::string& from, const std::string& edge, const std::string& to) const {
	std::cout << from << " -> " << to << " (" << edge << ")\n";
	return true;
}

/*
	Add information about the keys. For every zone we add which keys can be found there.
	map: zone -> set(keys)
*/
bool MapZone::addKey(const std::string& key, const std::string& node) {
	//	Optimization was done!
	//keys.push_back(std::make_pair(key, node));
	//keys[node].push_back(key);
	keys[node].insert(key);
	return true;
}

bool MapZone::printGraphKeys() const {
	int size = keys.size();
	for (KeysConstIterator it = keys.begin(); it != keys.end(); it++) {
		std::cout << it->first << ":\n";
	}
	return true;
}

void MapZone::analyzeAndGenerate(const std::string& start) {
	Set collectedKeysSet;
	
	std::string nextNode = start;
	Set visitedNodes;
	std::fstream file("result.dot", std::ios::out | std::ios::trunc);

	file << "digraph {\n";

	BFS_traverse(nextNode, nextNode, collectedKeysSet, visitedNodes, file);

	for (KeysIterator it = keys.begin(); it != keys.end(); it++) {
		file << it->first;
		file << "[label=\"";
		file << it->first;
		for (Set::iterator vIt = it->second.begin(); vIt != it->second.end(); vIt++) {
			file << "\\l";
			file << *vIt;
		}
		file << "\"];\n";
	}

	file << "}\n";

	file.close();
}