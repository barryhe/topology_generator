#include <set>
#include <vector>
#include <string>

class Node {
public:
	Node(int num_edges, std::string id, std::vector<std::string> & hostNames, class Domain * pDomain);

	void addNeighbor(Node * neighbor); 
	const std::set<Node*> getNeighbors() { return neighbors; }
	int getNumNeighbors() { return num; }
	const std::vector<std::string> & getHosts() { return hosts; }
	std::string getId() { return id; }
private:
	int num; 

	std::set<Node*> neighbors;

	std::vector<std::string> hosts; 

	class Domain * mDomain;

	std::string id;
};