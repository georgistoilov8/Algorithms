#pragma once

#ifndef MAPZONE_HEADER
#define MAPZONE_HEADER

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <queue>
#include <fstream>

/*
	Here we have graph constructed from Nodes and Edges.
	The nodes will be the zones from the file and the 
	edges will be the keys between zones if they are 
	needed.

	This class will represent a map.
	"Nodes" : are the zones on the map.
	"Edges" : connections between the zones and the keys that are needed to go from one zone to another
	"Keys": store information about the keys and in which zone they can be found.
*/

class MapZone {
	struct VisitData {
		const std::string* from;
		const std::string* to;
		const std::string* edge;

		VisitData(const std::string* from, const std::string* to, const std::string* edge)
			:from(from),
			 to(to),
			 edge(edge)
		{}
	};

	public:
		typedef std::unordered_map<std::string, std::string> Edges;
		typedef std::unordered_map<std::string, Edges> Nodes;

		typedef Edges::iterator EdgesIterator;
		typedef Nodes::iterator NodesIterator;

		//typedef std::vector<std::string> Vector;
		typedef std::unordered_set<std::string> Set;

		typedef std::unordered_map<std::string, Set> Keys;
		typedef Keys::const_iterator KeysConstIterator;
		typedef Keys::iterator KeysIterator;

	private:
		Nodes graph;
		Keys keys;

	public:
		MapZone();
		MapZone(const MapZone& other) = delete;
		MapZone& operator=(const MapZone& rhs) = delete;
		~MapZone();

		bool addNode(const std::string& node);

		bool addEdge(const std::string& from, const std::string& to, const std::string& edge);

		bool BFS_traverse(const std::string& start, std::string& nextNode, Set& collectedKeys, Set& alreadyVisitedZones, std::fstream& file);
		
		void analyzeAndGenerate(const std::string& start);

	private:
		bool printGraphNodes(const std::string& from, const std::string& edge, const std::string& to) const;

	public:
		bool addKey(const std::string& key, const std::string& node);

	private:
		bool printGraphKeys() const;
};

#endif // !MAPZONE_HEADER
