#pragma once

#ifndef AUTOMATA_HEADER
#define AUTOMATA

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>	// For std::sort
#include <queue>

class Automata {
	const static int alphabet_size = 256;

	struct Node {
		std::unordered_map<char, Node*> transitions;
		int number;
		bool final_state;
	};

private:
	int states_count;

	Node* initial_state;
	std::vector<std::string> words;
	std::vector<Node*> minimal_states;
	//std::unordered_map<Node*, std::vector<Node*>> connections;
	
	
public:
	Automata();
	Automata(const Automata& other) = delete;
	Automata& operator=(const Automata& rhs) = delete;
	~Automata();

	void construct(std::vector<std::string>& words);

	bool search(const std::string& str);
	void suggestions(Node* state, std::string prefix, int& k);
	void printAutoSuggestions(const std::string& prefix, int k);
	void addWord(const std::string& str);
	void printMemoryUsage();
private:

	Node* initializeNewNode();
	bool isFinal(Node* state) const;
	void setFinal(Node* state, bool state_condition);
	Node* transition(Node* state, char symbol);
	void setTransition(Node* state, char symbol, Node* next_state);
	void setNumber(Node* state, int number);

	Node* copyState(Node* state);
	void clearState(Node* state);
	int compareStates(Node* state1, Node* state2);

	Node* findMinimizedState(Node* state);
	Node* isMember(Node* state);
	void insert(Node* state);
};

#endif // !AUTOMATA_HEADER
