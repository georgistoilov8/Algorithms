#include "automata.h"

Automata::Automata() {
	states_count = 0;
}

Automata::~Automata() {
	for (unsigned i = 0; i < minimal_states.size(); i++) {
		delete minimal_states[i];
	}
	states_count = 0;
	initial_state = nullptr;
}

/* 
	Create new state
	@return - the new state
*/
Automata::Node* Automata::initializeNewNode() {
	Node* new_state = new Node;
	setFinal(new_state, false);
	setNumber(new_state, states_count);

	states_count++;
	return new_state;
}
/*
	Check if state is final.
	@param state - The state we want to check if it is final.
	@return - True if the state is final and false otherwise.

*/
bool Automata::isFinal(Node* state) const {
	return state->final_state;
}

/*
	Set the state to be final or not.
	@param state - The state we want to set.
	@param condition - The condition we want to leave the state.
*/
void Automata::setFinal(Node* state, bool condition) {
	state->final_state = condition;
}

/*
	Check for transition between two states with certain symbol.
	@param state - The initial state, from which the transition starts.
	@param symbol - The character for the transition.
	@return - If from the initial state there is transition to another state
			  with the character, then return the reached state. If there isn't
			  such a transition then return nullptr.
*/
Automata::Node* Automata::transition(Node* state, char symbol) {
	std::unordered_map<char, Node*>::iterator it = state->transitions.find(symbol);
	if (it == state->transitions.end()) {
		return nullptr;
	}
	return it->second;
}

/*
	Create transition between two states with certain character.
	@param state - State from which the transition will begin.
	@param symbol - Character of the transition.
	@param next_state - The state, in which the transition will end.
*/
void Automata::setTransition(Node* state, char symbol, Node* next_state) {
	state->transitions[symbol] = next_state;
}

void Automata::setNumber(Node* state, int number) {
	state->number = number;
}

/*
	Create copy of an already existing state.
	@param state - The state we want to make copy of.
	@return - Return the copy.
*/
Automata::Node* Automata::copyState(Node* state) {
	Node* new_state = initializeNewNode();
	setFinal(new_state, isFinal(state));
	
	for (std::unordered_map<char, Node*>::iterator it = state->transitions.begin(); it != state->transitions.end(); it++) {
		setTransition(new_state, it->first, it->second);
	}
	return new_state;
}

/*
	Clear all transitions from state and make it not final.
	@param state - The state we want to clear.
*/
void Automata::clearState(Node* state) {
	setFinal(state, false);
	state->transitions.clear();
	state->number = 0;
}

/*
	Check if two states are equal.
	@param state1 - First state.
	@param state2 - Second state.
	@return - Returns 0 if they are equal and 1 if they are not.
*/
int Automata::compareStates(Node* state1, Node* state2) {
	if (isFinal(state1) != isFinal(state2)) {
		return 1;
	}
	int size1 = state1->transitions.size();
	int size2 = state2->transitions.size();
	if (size1 != size2) {
		return 1;
	}
	for (std::unordered_map<char, Node*>::iterator it = state1->transitions.begin(); it != state1->transitions.end(); it++) {
		if (transition(state1, it->first) != transition(state2, it->first)) {
			return 1;
		}
	}
	return 0;
}

/*
	Direct construction of Minimal Acyclic Finite States Automata.
	The algorithm which is used is by Stoyan Mihov.
	Steps:
		1. Sort the words, which are given.
		2. For each word find the common prefix with the previous word.
		3. If there is a common prefix, skip it and start to add transitions
		   after the prefix.
		4. Repeat 2 and 3 for all words. Eventually we will have minimal
		   automata.
	Time complexity: O(n*log(m)), where n is the number of all symbols in
	in the words and m is the number of states.
	Space complexity: O(m), where m is the number of states.

	За жалост, при мен мисля, че сложността е О(n*m) и затова е доста
	бавно... :'(

	@param words - Array of words
*/
void Automata::construct(std::vector<std::string>& words) {
	int words_size = words.size();
	std::sort(words.begin(), words.end());
	std::cout << "Words sorted.\n";
	
	unsigned max_words_size = 0;
	for (std::vector<std::string>::iterator it = words.begin(); it != words.end(); it++) {
		if (max_words_size < (*it).size()) {
			max_words_size = (*it).size();
		}
	}
	max_words_size = max_words_size + 1;
	std::vector<Node*> temp_states(max_words_size);
	std::string previous_word;
	std::string current_word;
	for (unsigned i = 0; i < max_words_size; i++) {
		temp_states[i] = initializeNewNode();
	}

	previous_word = "";
	clearState(temp_states[0]);
	std::cout << "Start constructing automata...\n";
	int counter = 0;
	while (counter < words_size) {
		current_word = words[counter];
		unsigned prefix_length = 0;

		while (prefix_length < current_word.size() && prefix_length < previous_word.size() && previous_word[prefix_length] == current_word[prefix_length]) {
			prefix_length++;
		}
		for (unsigned i = previous_word.size(); i > prefix_length; i--) {
			setTransition(temp_states[i - 1], previous_word[i-1], findMinimizedState(temp_states[i]));
		}
		for (unsigned i = prefix_length + 1; i <= current_word.size(); i++) {
			clearState(temp_states[i]);
			setTransition(temp_states[i - 1], current_word[i-1], temp_states[i]);
		}

		setFinal(temp_states[current_word.size()], true);
		previous_word = current_word;
		counter++;
	}

	for (int i = current_word.length(); i >= 1; i--) {
		setTransition(temp_states[i - 1], previous_word[i-1], findMinimizedState(temp_states[i]));
	}
	
	std::cout << "End of constructing automata...\n";

	initial_state = findMinimizedState(temp_states[0]);
	std::cout << "States in the automata: " << minimal_states.size() << std::endl;
	
	for (unsigned i = 0; i < temp_states.size(); i++) {
		delete temp_states[i];
	}
}

void Automata::addWord(const std::string& word) {
	std::vector<std::string> temp_arr;
	temp_arr.push_back(word);
	construct(temp_arr);
}

void Automata::printMemoryUsage() {
	size_t memory = 0;
	//Node* current_state = initial_state;
	//memory += sizeof(*current_state);
	std::queue<Node*> queue;
	queue.push(initial_state);
	while (!queue.empty()) {
		Node* temp_state = queue.front();
		queue.pop();
		memory += sizeof(*temp_state);
		for (std::unordered_map<char, Node*>::iterator it = temp_state->transitions.begin(); it != temp_state->transitions.end(); it++) {
			queue.push(it->second);
		}
	}
	memory += sizeof(minimal_states);
	std::cout << memory;
}

/*
	Check if the state is in the minimal automata. If it's not,
	then create a copy of the state and insert it into the automata.
	@param state - The state we want to check
	@return - Returns the state which is already in the automata.
*/
Automata::Node* Automata::findMinimizedState(Node* state) {
	Node* current = isMember(state);
	if (!current) {
		Node* temp = copyState(state);
		//connections[state].push_back(n);
		insert(temp);
		return temp;
	}
	return current;
}

/*
	Check if a state is in the current minimal automata.
	@param state - The state we want to check
	@return - The state in the minimal automata if it's in there
	or nullptr.

	Тук се крие разковничето за бавното зареждане на думите...
*/
Automata::Node* Automata::isMember(Node* state) {
	int size = minimal_states.size();
	//std::cout << size << std::endl;
	/*std::unordered_map<Node*, std::vector<Node*>>::iterator it = connections.find(state);
	if (it == connections.end()) {
		//std::cout << "State: " << state << std::endl;
		return nullptr;
	}
	int size_vector = it->second.size();
	for (int i = 0; i < size_vector; i++) {
		if (compareStates(state, it->second[i]) == 0) {
			return it->second[i];
		}
	}*/

	for (int i = 0; i < size; i++) {
		if (compareStates(state, minimal_states[i]) == 0) {
			return minimal_states[i];
		}
	}
	return nullptr;
}

/*
	Add state to the minimal automata.
	@param - The state we want to include.
*/
void Automata::insert(Node* state) {
	minimal_states.push_back(state);
}

/*
	Find and print suggestions.
	@param state - Current state.
	@param prefix - Current prefix.
	@param k - Number of remaining suggestions to print.
*/
void Automata::suggestions(Node* state, std::string prefix, int& k) {
	if (k <= 0) {
		return;
	}

	if (state->final_state) {
		std::cout << prefix << std::endl;
		k--;
	}	

	if (state->transitions.size() == 0) {
		return;
	}

	for (std::unordered_map<char, Node*>::iterator it = state->transitions.begin(); it != state->transitions.end(); it++) {
		prefix.push_back(it->first);
		suggestions(it->second, prefix, k);
		prefix.pop_back();
	}
}

/*
	Find prefix in the automata and start printing suggestions
	@param prefix - The prefix we want to find.
	@param k - Number of suggestions.
*/
void Automata::printAutoSuggestions(const std::string& prefix, int k) {
	if (!initial_state) {
		std::cout << "No matching found.\n";
		return;
	}

	int str_size = prefix.size();
	Node* current_state = initial_state;
	std::unordered_map<char, Node*>::iterator it;
	for (int i = 0; i < str_size; i++) {
		it = current_state->transitions.find(prefix[i]);
		if (it == current_state->transitions.end()) {
			std::cout << "Word not found. No available suggestions.\n";
			return;
		}
		current_state = it->second;
	}

	bool isWord = false;
	if (current_state && current_state->final_state) {
		isWord = true;
	}

	bool isLeaf = false;
	if (current_state->transitions.size() == 0) {
		isLeaf = true;
	}

	if (isWord && isLeaf) {
		std::cout << prefix << std::endl;
	}

	if (!isLeaf) {
		int temp = k;
		std::string query = prefix;
		std::cout << "Suggestions: \n";
		suggestions(current_state, query, temp);
		std::cout << "----------------------------\n";
	}
}

/*
	Check if string is recognizable from the automata
	@param str - string to check
	@return - true if string is recognizable and false otherwise
*/
bool Automata::search(const std::string& str) {
	if (!initial_state) {
		return false;
	}

	int str_size = str.size();
	Node* current_state = initial_state;
	std::unordered_map<char, Node*>::iterator it;
	for (int i = 0; i < str_size; i++) {
		it = current_state->transitions.find(str[i]);
		if (it == current_state->transitions.end()) {
			return false;
		}
		current_state = it->second;
	}
	if (current_state && current_state->final_state) {
		return true;
	}
	return false;
}

/*  Just information:
	Before this algorithm, I tried to realize the Hopcroft algorithm.
	It was almost done and you can find it if you want in the last of
	the commented functions - minimize. It just miss some edge cases.
	When I tested it, it didn't go in this edge cases. What I found out
	was, that it was slow algorithm, slower than the current one.
	Steps:
		1. First we need to construct Trie. 
		2. This Trie need to be total, so for each missing
		   transition with letter we create one to reject state.
		3. After step 1 and 2 we have Deterministic finite automaton.
		   For this DFA we apply the Hopcroft algorithm for minimization
		   of DFA.

	Steps of Hopcrofts algorithm:
		1. Separete states in two: final and not final states. P:={F, Q\F};
		2. Create array for all final states. {W}
		3. For each state "A" in W we do:
			3.1. For each letter "c" in the alphabet:
				3.1.1. Create X - set of states for which
				a transition on "c" leads to a state in "A"
				3.1.2. For each set Y in P for which X intersects Y
				is not empty and Y\X is not empty we do:
					3.1.2.1. Replace Y in P by the two sets: X intersects Y and Y \ X
					3.1.2.2. If Y is in W => replace Y in W by the same two sets
							 Else
								If |X intersects Y| <= |Y \ X|
									add X intersects Y to W
								Else
									add Y \ X to W
*/

/*
	void Automata::addWord(const std::string& word) {
		words.push_back(word);
	}

	
	Add string to the language of the automata
	@param str - string, which we want to be added
	void Automata::insert(const std::string& str) {
		int str_size = str.size();
		Node* current_state = start_state;

		for (int i = 0; i < str_size; i++) {
			int index = str[i];
			if (!current_state->next_states[index]) {
				current_state->next_states[index] = initializeNewNode();
			}
			current_state = current_state->next_states[index];
		}

		current_state->final_state = true;
	}

	/*
	Make the automata total. From every state to every state there is
	a transition

	void Automata::supplementingToTotal() {
		std::cout << "Total...\n";
		Node* current_state = start_state;
		makeTotal(current_state);
	}

	void Automata::makeTotal(Node* state) {
		if (isLastNode(state)) {
			for (int i = 0; i < alphabet_size; i++) {
				if (!state->next_states[i]) {
					state->next_states[i] = reject_state;
				}
			}
			return;
		}
		for (int i = 0; i < alphabet_size; i++) {
			if (state->next_states[i]) {
				makeTotal(state->next_states[i]);
			}
		}
		for (int i = 0; i < alphabet_size; i++) {
			if (!state->next_states[i]) {
				state->next_states[i] = reject_state;
			}
		}
	}

	bool Automata::isLastNode(Node* state){
		for (int i = 0; i < alphabet_size; i++) {
			if (state->next_states[i]) {
				return false;
			}
		}
		return true;
	}

	void Automata::generateFile(std::fstream& file, Node* state) const {
		if (!state) {
			return;
		}
		for (int i = 0; i < alphabet_size; i++) {
			if (state->next_states[i]) {
				file << state->number;
				file << "->";
				file << state->next_states[i]->number;
				file << "[label=\"";
				file << (char)i;
				file << "\"];\n";
				if (state->next_states[i]->final_state) {
					file << state->next_states[i]->number;
					file << "[color=red,style=filled, fillcolor=\"#ffefef\"];\n";
				}
			}
		}
		for (int i = 0; i < alphabet_size; i++) {
			if (state->next_states[i] && state->next_states[i] != reject_state) {
				generateFile(file, state->next_states[i]);
			}
		}
	}
	void Automata::generateDotFile() const {
		std::fstream file("result.dot", std::ios::out | std::ios::trunc);
		file << "digraph {\n";
		generateFile(file, start_state);
		file << "}\n";
		file.close();	
	}

	void Automata::findEquivalenceClasses(std::unordered_map<int, std::vector<Node*>>& states) {
		bool new_equivalence_class = false;

		std::unordered_map<int, std::vector<Node*>>::iterator classes_it;
		std::vector<Node*>::iterator states_it;

		for (classes_it = states.begin(); classes_it != states.end(); classes_it++) {
			if (classes_it->second.size() != 0) {
				Node* first_state = classes_it->second[0];
				for (states_it = classes_it->second.begin(); states_it != classes_it->second.end(); states_it++) {
					bool equivalent = true;
					for (int i = 0; i < alphabet_size; i++) {
						if (first_state.next_states[i] != states_it->next_states[i]) {
							equivalent = false;
							break;
						}
					}
					if (!equivalent) {
						// make std::unordered_map<int, std::vector<std::pair<Node, bool>>>
						//classes_it->second.second = false;
					}
				}
			}

		}

		if (new_equivalence_class) {
			findEquivalenceClasses(states);
		}
	}

	void Automata::fillStates(StateClasses& states, QueueNode& W, Node* current_state) {
		if (!current_state || current_state == reject_state) {
			return;
		}
		if (current_state->final_state) {
			states[0].push_back(current_state);
		}
		else {
			// Not final states
			W.push(current_state);
			states[1].push_back(current_state);
		}

		for (int i = 0; i < alphabet_size; i++) {
			fillStates(states, W, current_state->next_states[i]);
		}
	}

	void Automata::minimize() {
		std::cout << "Minimization ...\n";
		supplementingToTotal();
		StateClasses P;
		VectorNode final_states;
		VectorNode non_final_states;
		QueueNode W;
		P.insert(std::make_pair(0, final_states));
		P.insert(std::make_pair(1, non_final_states));
		equivalent_classes_count = 2;
		P[1].push_back(reject_state);
		fillStates(P, W, start_state);
		//Предполагаме, че сме на ниво: Имаме P и W
		//findEquivalenceClasses(states);
		//clear(start_state);
		bool shouldUpdateClasses = false;
		//std::queue<int> countClasses;
		while (!W.empty()) {
			Node* current_state = W.front();
			W.pop();
			//std::cout << current_state.number << std::endl;
			for (int i = 0; i < alphabet_size; i++) {
				VectorNode X;
				for (StateClasses::iterator it = P.begin(); it != P.end(); it++) {
					for (VectorNode::iterator it_v = it->second.begin(); it_v != it->second.end(); it_v++) {
						//std::cout << (*it_v)->next_states[i]->number << std::endl;
						if (current_state == (*it_v)->next_states[i]) {
							X.push_back( (*it_v)->next_states[i]);
						}
					}
				}
				// Намерили сме Х.
				//std::cout << X.size() << std::endl;
				//std::cout << "-----\n";

				std::sort(X.begin(), X.end());
				//std::cout << X.size() << std::endl;
				//countClasses = 0;
				for (StateClasses::iterator it = P.begin(); it != P.end(); it++) {
					VectorNode intersection;
					VectorNode difference;
					std::sort(it->second.begin(), it->second.end());
					std::set_intersection(X.begin(), X.end(), it->second.begin(), it->second.end(), back_inserter(intersection));
					std::set_difference(it->second.begin(), it->second.end(), X.begin(), X.end(), std::inserter(difference, difference.begin()));
					/*if (intersection.size() > 0 || difference.size() > 0) {
						std::cout << intersection.size() << std::endl;
						std::cout << difference.size() << std::endl;
						std::cout << "----\n";
					}*/
					/*if (!intersection.empty() && !difference.empty()) {
						//shouldUpdateClasses = true;
						// remove nodes

						VectorNode temp;
						for (VectorNode::iterator v_it = it->second.begin(); v_it != it->second.end(); v_it++) {
							VectorNode::iterator iter = std::find(X.begin(), X.end(), *v_it);

							if (iter == X.end()) {
								// Element not found
								temp.push_back(*v_it);
							}

						}
						it->second = temp;

						//Node* firstOfX = X[0];
						// Check for already
						P[equivalent_classes_count] = X;
						equivalent_classes_count++;

						if (intersection.size() <= difference.size()) {
							for (VectorNode::iterator v_it = intersection.begin(); v_it != intersection.end(); v_it++) {
								W.push(*v_it);
							}
						}
						else {
							for (VectorNode::iterator v_it = difference.begin(); v_it != difference.end(); v_it++) {
								W.push(*v_it);
							}
						}
						break;
					}
				}
			}

		}
		std::cout << P.size() << std::endl;
		std::cout << states_count << std::endl;
	}
*/