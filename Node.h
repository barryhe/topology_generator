#include <set>

class Node {
public:
	Node(int num_edges);

	void addNeighbor(Node * neighbor); 
	const std::set<Node*> getNeighbors() { return neighbors; }
	int getNumNeighbors() { return num; }
private:
	int num; 
	std::set<Node*> neighbors;
};