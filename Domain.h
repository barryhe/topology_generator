#include <vector>
#include <unordered_set>
#include <set>
#include <string>

class Domain {
public:
	Domain(std::string did, int num_domains, int num_hosts, int num_nodes, int num_edges, int num_borders, 
			std::vector<std::string> & nodeNames,
			std::vector<std::string> & hostNames, 
			class Manager *pManager);
	~Domain();

	const std::vector<class Node*> & getNodes() {
		return nodes;
	}
	const std::vector<class Node*> getBorderNodes() {
		return borders;
	}

	std::string & getId() { return id; }

	void runRegularGraph();

	// Node * getRandomBorderNode (); 

private:
	std::vector<class Node*> nodes;
	std::vector<class Node*> non_borders; 
	std::vector<class Node*> borders; // can 

	std::string id;
	class Manager * mManager;
}; 