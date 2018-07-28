#include <set>
#include <vector>
#include <string>

class Node {
public:
	Node(int num_edges, std::vector<std::string> & hostNames);

	void addNeighbor(Node * neighbor); 
	const std::set<Node*> getNeighbors() { return neighbors; }
	int getNumNeighbors() { return num; }
private:
	int num; 
	std::set<Node*> neighbors;

	std::vector<std::string> hosts; 
};