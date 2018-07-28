#include <vector>
#include <unordered_set>
#include <set>
#include <string>

class Domain {
public:
	Domain(int num_domains, int num_hosts, int num_nodes, int num_edges, int num_borders, 
			std::vector<std::string> & nodeNames,
			std::vector<std::string> & hostNames, 
			class Manager *pManager);
	~Domain();

	const std::set<class Node*> getNodes() {
		return nodes;
	}
	const std::set<class Node*> getBorderNodes() {
		return borders;
	}

private:
	std::set<class Node*> nodes;
	std::set<class Node*> non_borders; 
	std::set<class Node*> borders; // can 

	std::string generateRandomId(); 

	class Manager * mManager;
}; 