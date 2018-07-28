#include <vector>


class Manager {
public:
	Manager(int num_domains, int num_hosts, int num_nodes, int num_edges, int num_borders);
	~Manager();
private:
	std::vector<class Domain *> domains;
	std::string getRandomId(); 
};