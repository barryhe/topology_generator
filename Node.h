#include <set>
#include <vector>
#include <string>

class Node {
public:
	Node(int num_edges, std::string id, std::vector<std::string> & hostNames, class Domain * pDomain);

	void addNeighbor(Node * neighbor); 
	const std::vector<Node*> getNeighbors() { return neighbors; }
	int getNumNeighbors() { return num; }
	const std::vector<std::string> & getHosts() { return hosts; }
	std::string getId() { return id; }
	bool isBorder() { return hosts.size() == 0; }

	int getBorderNeighborCounts() { return border_nodes; }

private:
	int num; 
	std::vector<Node*> neighbors;
	std::vector<std::string> hosts; 
	class Domain * mDomain;
	class Domain * getDomain() { return mDomain; }
	std::string id;

	int border_nodes; 
};